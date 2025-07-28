#include <cmath>
#include <iostream>
#include <stdexcept>
#include "../option.h"

using option::Option;

Option<float> Fraction(float num, float den) {
  if (fabsf(den) <= static_cast<float>(1e-6))
    return option::none;  // return {} or option::none
  return Option<float>(num / den);
}
// you can also use implicit conversion to keep function cleeaner
Option<float> FractionCast(float num, float den) {
  if (fabsf(den) <= static_cast<float>(1e-6))
    return {};
  return num / den;
}

int main() {
  auto fractionWorks = Fraction(1.2f, 0.1f);
  std::cout << "Sucessfull: " << fractionWorks.has_value() << std::endl;
  if (fractionWorks.has_value())
    std::cout << fractionWorks.value() << std::endl;

  auto fractionDoesntWork = Fraction(1.2f, 0.0f);
  std::cout << "Sucessfull: " << fractionDoesntWork.has_value() << std::endl;
  if (!fractionDoesntWork)
    std::cout << "Function failed, please check you inputs!" << std::endl;
  // this code shows, that if you try to access data on no-success, a runtime_error is risen
  try {
    auto _ = fractionDoesntWork.value();
  } catch (const option::bad_optional_access& e) {
    std::cout << "Getting data failed due to: " << e.what() << std::endl;
  }

  auto fractionCast = FractionCast(1.2f, 0.1f);
  if (fractionCast)
    std::cout << "Success: " << *fractionCast << std::endl;
  else
    std::cout << "No Success" << std::endl;
}
