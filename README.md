# Option

Very lightweight implementation of Rust like Option type for C++.
I created it to keep dataflow more organised on embedded hardware with small types like uints and floats.
For more complex usage use things like the <expected> header in C++23.

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
        return Option<float>(); // empty option -> error
    return num/den; // casts automatically to Option<float>(true, num / den)
}

int main() {
    auto f = Fraction(1.2f, 0.1f);
    std::cout << "Sucessfull: " << f.Success() << std::endl;
    if (f.Success())
        std::cout << f.Data() << std::endl;
}
```
