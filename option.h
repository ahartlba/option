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
#include <iostream>
#include <stdexcept>
#include <type_traits>
#include <utility>

namespace option {

class bad_optional_access : public std::exception {
 public:
  const char* what() const noexcept override {
    return "bad optional access; no value assigned";
  }
};

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

  Option(T&& value) noexcept(std::is_nothrow_move_constructible<T>::value)
      : has_value_(true) {
    new (storage_) T(std::move(value));
  }

  Option(const Option& other) : has_value_(other.has_value_) {
    if (has_value_) {
      new (storage_) T(*other);
    }
  }

  Option(Option&& other) noexcept(std::is_nothrow_move_constructible<T>::value)
      : has_value_(other.has_value_) {
    if (has_value_) {
      new (storage_) T(std::move(*other));
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

  Option& operator=(Option&& other) noexcept(
      std::is_nothrow_move_assignable<T>::value) {
    if (this != &other) {
      reset();
      if (other.has_value_) {
        new (storage_) T(std::move(*other));
        has_value_ = true;
      }
    }
    return *this;
  }

  bool has_value() const noexcept { return has_value_; }
  explicit operator bool() const noexcept { return has_value_; }
  T& value() {
    if (!has_value_)
      throw bad_optional_access();
    return *ptr();
  }

  const T& value() const {
    if (!has_value_)
      throw bad_optional_access();
    return *ptr();
  }

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
    new (storage_) T(std::forward<Args>(args)...);
    has_value_ = true;
  }
};
}  // namespace option
