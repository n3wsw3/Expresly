# Expresly

A parser and evaluater for expressions using [this](https://blog.kallisti.net.nz/2008/02/extension-to-the-shunting-yard-algorithm-to-allow-variable-numbers-of-arguments-to-functions/) variation of the Shunting yard algorithm.

## Getting Started

If you're not going to run any tests then you can clone the project with `git clone https://github.com/n3wsw3/Expresly`.

### Running Tests

Since the tests depend on gtest you have to recursivly clone the submodules.

Start by cloning the repository with `git clone --recursive https://github.com/n3wsw3/Expresly`.
If the repository was cloned non-recursively previously, use `git submodule update --init` to clone the necessary submodules.

## Examples

### Simple with only standard operators and functions

```cpp
#include "expresly.hpp"
#include <iostream>

int main() {
  std::cout << Expresly::expression::eval("(2 + 2)") << std::endl;
  return 0;
}
```

Will output 4

### With added functions

```cpp
#include "expresly.hpp"
#include <iostream>
#include <cmath>

int main() {
  Expresly::Options op = Expresly::Options();
  op.addFunction("mod", [](std::vector<double> v) {
		return std::fmod(v[1], v[0]);
  });

  std::cout << Expresly::expression::eval("mod ( 2 + 3 , 2 )", op); << std::endl;
  return 0;
}
```

Will output 1
