#include <iostream>
#include "../option.h"

int main() {
  static_assert(std::is_same<optionlib::remove_reference<int>::type, int>::value, "int");
  static_assert(std::is_same<optionlib::remove_reference<int&>::type, int>::value, "int&");
  static_assert(std::is_same<optionlib::remove_reference<int&&>::type, int>::value, "int&&");

  std::cout << "All static asserts passed!\n";
  return 0;
}
