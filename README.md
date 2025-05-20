# Option

Very lightweight implementation of Rust like Option type for C++.

## Example

```c++
#include "option.h"
#include <cmath>
#include <iostream>

Option<float> Fraction(float num, float den) {
    if (fabsf(den) <= static_cast<float>(1e-6))
        return Option<float>(false);
    return Option<float>(true, num / den);
}

int main() {
    auto f = Fraction(1.2f, 0.1f);
    std::cout << "Sucessfull: " << f.Success() << std::endl;
    if (f.Success())
        std::cout << f.Data() << std::endl;
}
```
