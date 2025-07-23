# Option

Very lightweight implementation of Rust like Option type for C++.

## Installation

Clone repository using submodules, or download raw-file from `https://raw.githubusercontent.com/ahartlba/option/refs/heads/main/option.h`.

### Using Curl

An example using curl to download. Set your path to where you want to download file to and run

```shell
curl https://raw.githubusercontent.com/ahartlba/option/refs/heads/main/option.h > option.h
```

## Example

```c++
#include "option.h"
#include <cmath>
#include <iostream>

Option<float> Fraction(float num, float den) {
    if (fabsf(den) <= static_cast<float>(1e-6))
        return Option<float>(false);
    return num/den; // casts automatically to Option<float>(true, num / den)
}

int main() {
    auto f = Fraction(1.2f, 0.1f);
    std::cout << "Sucessfull: " << f.Success() << std::endl;
    if (f.Success())
        std::cout << f.Data() << std::endl;
}
```
