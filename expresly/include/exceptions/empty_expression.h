#pragma once
#include <exception>
#include <sstream>
#include <string>

namespace Expresly {
class empty_expression : public std::exception {
 public:
  const char* what() const throw() { return "Expression is empty"; }
};
}  // namespace Expresly