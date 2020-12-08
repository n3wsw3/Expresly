#pragma once

#include <string>

#include "types.h"

namespace expresly {
class Token {
 public:
  enum class Type {
    Unknown = 0,
    Number,
    Operator,
    Function,
    LeftParam,
    RightParam,
    FunctionDelimiter
  };
  Token();
  Token(Type);
  Token(Type, const std::string&);
  Token(Type, std::string&&);
  Token(Type, const std::string&, int, bool, FuncParam);
  Token(Type, std::string&&, int, bool, FuncParam);

  Type type{Type::Unknown};
  std::string string{};
  int precedence{-1};
  bool rightAssociative{false};
  int arguments{-1};
  FuncParam function{nullptr};
  double value{-1};
};
}  // namespace expresly