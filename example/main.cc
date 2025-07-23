#include <cmath>
#include <iostream>
#include <stdexcept>
#include "../option.h"

Option<float> Fraction(float num, float den) {
  if (fabsf(den) <= static_cast<float>(1e-6))
    return Option<float>(); // empty option -> error
  return Option<float>(num / den);
}
// you can also use implicit conversion to keep function cleeaner
Option<float> FractionCast(float num, float den) {
  if (fabsf(den) <= static_cast<float>(1e-6))
    return Option<float>();
  return num/den;
}

int main() {
  auto fractionWorks = Fraction(1.2f, 0.1f);
  std::cout << "Sucessfull: " << fractionWorks.Success() << std::endl;
  if (fractionWorks.Success())
    std::cout << fractionWorks.Data() << std::endl;

  auto fractionDoesntWork = Fraction(1.2f, 0.0f);
  std::cout << "Sucessfull: " << fractionDoesntWork.Success() << std::endl;
  if (!fractionDoesntWork.Success())
    std::cout << "Function failed, please check you inputs!" << std::endl;
  // this code shows, that if you try to access data on no-success, a runtime_error is risen
  try {
    auto _ = fractionDoesntWork.Data();
  } catch (const std::runtime_error& e) {
    std::cout << "Getting data failed due to: " << e.what() << std::endl;
  }

  auto fractionCast = FractionCast(1.2f, 0.1f);
  if (fractionCast.Success())
    std::cout << "Success: " << fractionCast.Data() << std::endl;
  else
    std::cout << "No Success" << std::endl;
}
