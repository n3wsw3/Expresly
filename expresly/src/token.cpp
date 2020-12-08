#include "token.h"

#include <string>

namespace expresly {

Token::Token() {}
Token::Token(Type type) : type{type} {}

Token::Token(Type type, const std::string& expression)
    : type{type}, string{expression} {
  if (type == Type::Number) value = std::stod(string);
}

Token::Token(Type type, std::string&& expression)
    : type{type}, string{std::move(expression)} {
  if (type == Type::Number) value = std::stod(string);
}

Token::Token(Type type, const std::string& expression, int precedence,
             bool rightAssociative, FuncParam function)
    : type{type},
      string{expression},
      precedence{precedence},
      rightAssociative{rightAssociative},
      function{function} {}

Token::Token(Type type, std::string&& expression, int precedence,
             bool rightAssociative, FuncParam function)
    : type{type},
      string{std::move(expression)},
      precedence{precedence},
      rightAssociative{rightAssociative},
      function{function} {}
}  // namespace expresly