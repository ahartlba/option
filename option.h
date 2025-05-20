#pragma once

template <typename T>
class Option {
 private:
  bool m_Success;
  T m_Data;

 public:
  Option(bool success) : m_Success(success) {};
  Option(bool success, T data) : m_Success(success), m_Data(data) {};

  [[nodiscard]] inline bool Success() const { return m_Success; }
  [[nodiscard]] inline T Data() const { return m_Data; }
};
