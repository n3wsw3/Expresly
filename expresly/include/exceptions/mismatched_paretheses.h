#pragma once
#include <exception>
#include <sstream>
#include <string>

namespace Expresly {
class mismatched_parentheses : public std::exception {
 public:
  const char* what() const throw() { return "Mismatched parentheses"; }
};
}  // namespace Expresly