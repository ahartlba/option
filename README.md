# Option

Very lightweight implementation of Rust like Option type for C++.
Heavily inspired by C++17 header `<optional>`.
I created it to keep dataflow more organised on embedded hardware with small types like uints and floats,
where i do not have access to the `<optional>` header.
If possible always use the `<expected>` header in C++23 or `<optional>` in C++17.

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
        return {};
    return num/den; 
}

int main() {
    auto f = Fraction(1.2f, 0.1f);
    std::cout << "Sucessfull: " << f.has_value()<< std::endl;
    if (f)
        std::cout << *f << std::endl;
}
```
