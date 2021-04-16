#pragma once
#include <memory>
#include <span>
#include <string>

namespace expresly {

enum class token_type {
  None,
  Operator,
  Unary,
  Variable,
  Function,
  Delimiter,
  Decimal,
  Integer,
  Boolean
};

class token {
 private:
  const std::string names;

 public:
  token_type type{token_type::None};
  token(const std::string& _name, token_type _type)
      : names(_name), type(_type) {}

  const bool isBoolean() const { return type == token_type::Boolean; }

  const bool isNumber() const {
    return type == token_type::Decimal || type == token_type::Integer;
  }

  const bool isOperator() const {
    return type == token_type::Operator || type == token_type::Unary;
  }

  const bool isFunction() const { return type == token_type::Function; }

  template <typename T>
  T* As() const {
    return (T*)(this);
  }

  token_number<int>* asInteger() const {
    switch (type) {
      case token_type::Decimal:
        return new token_number<int>(As<token_number<double>>()->value);
      case token_type::Boolean:
        return new token_number<int>(As<token_number<bool>>()->value);
      case token_type::Integer:
        return As<token_number<int>>();
      default:
        return new token_number<int>(0);
    }
  }

  const virtual std::string name() const { return names; }

  // const token_number<int> asInteger() const {return
  // static_cast<token_number<int>*>(this);}

  // const token_type type() const { return type; }
};
}  // namespace expresly