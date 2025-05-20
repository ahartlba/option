#include <cmath>
#include <iostream>
#include "../option.h"

Option<float> Fraction(float num, float den) {
  if (fabsf(den) <= static_cast<float>(1e-6))
    return Option<float>(false);
  return Option<float>(true, num / den);
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
}