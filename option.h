#pragma once

template <typename T>
class Option {
  private:
    bool m_Success;
    T m_Data;

  public:
    Option(bool success) : m_Success(success) {};
    Option(bool success, T data) : m_Success(success), m_Data(data) {};

    bool Success() { return m_Success; }
    T Data() { return m_Data; }
};
