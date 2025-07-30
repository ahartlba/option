/*
 * MIT License
 *
 * Copyright (c) 2025 Andreas Hartl-Bachinger
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
**/
#pragma once

/* optionlib
 * Library for custom implementation of stdlib functions
 * necessary to be as equal to <optional> as possible
 */
namespace optionlib {
template <typename T>
struct remove_reference {
  using type = T;
};
template <typename T>
struct remove_reference<T&> {
  using type = T;
};
template <typename T>
struct remove_reference<T&&> {
  using type = T;
};

template <typename T>
T&& forward(typename remove_reference<T>::type& t) {
  return static_cast<T&&>(t);
}

}  // namespace optionlib

namespace option {

struct none_t {
  explicit constexpr none_t(int) {}
};
constexpr none_t none{0};

template <typename T>
class Option {
 private:
  bool has_value_;
  alignas(T) unsigned char storage_[sizeof(T)];

  T* ptr() { return reinterpret_cast<T*>(storage_); }
  const T* ptr() const { return reinterpret_cast<const T*>(storage_); }

 public:
  Option() noexcept : has_value_(false) {}
  Option(none_t) noexcept : has_value_(false) {}
  Option(const T& value) : has_value_(true) { new (storage_) T(value); }
  Option(T&& value) : has_value_(true) { new (storage_) T(static_cast<T&&>(value)); }

  Option(const Option& other) : has_value_(other.has_value_) {
    if (has_value_) {
      new (storage_) T(*other);
    }
  }

  Option(Option&& other) : has_value_(other.has_value_) {
    if (has_value_) {
      new (storage_) T(static_cast<T&&>(*other));
    }
  }

  ~Option() { reset(); }

  Option& operator=(none_t) noexcept {
    reset();
    return *this;
  }

  Option& operator=(const Option& other) {
    if (this != &other) {
      reset();
      if (other.has_value_) {
        new (storage_) T(*other);
        has_value_ = true;
      }
    }
    return *this;
  }

  Option& operator=(Option&& other) {
    if (this != &other) {
      reset();
      if (other.has_value_) {
        new (storage_) T(static_cast<T&&>(*other));
        has_value_ = true;
      }
    }
    return *this;
  }

  bool has_value() const noexcept { return has_value_; }
  explicit operator bool() const noexcept { return has_value_; }

  // allow for access without raising error, so that it works embedded
  T& value() { return *ptr(); }
  const T& value() const { return *ptr(); }

  T value_or(T default_value) { return has_value() ? *ptr() : default_value; }

  T& operator*() { return value(); }
  const T& operator*() const { return value(); }

  T* operator->() { return &value(); }
  const T* operator->() const { return &value(); }

  void reset() noexcept {
    if (has_value_) {
      ptr()->~T();
      has_value_ = false;
    }
  }
  template <typename... Args>
  void emplace(Args&&... args) {
    reset();
    new (storage_) T(optionlib::forward<Args>(args)...);
    has_value_ = true;
  }
};
}  // namespace option
