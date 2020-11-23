#pragma once

#include <string>
#include "types.h"

namespace Expresly {
class Token
{
  public:
    enum Type
    {
        Unknown = 0,
        Number,
        Operator,
        Function,
        LeftParam,
        RightParam,
        FunctionDelimiter
    };
    Token() {}
    Token(Type t) : type{t} {}
    Token(Type t, std::string s) : type{t}, string{s}
    {
        if (t == Token::Type::Number)
        {
            value = stod(s);
        }
    }
    Token(Type t, std::string s, int prec, bool ra, FuncParam fu)
        : type{t}, string{s}, precedence{prec}, rightAssociative(ra), function(fu) {}

    Type type{Type::Unknown};
    std::string string{};
    int precedence{-1};
    bool rightAssociative{false};
    int arguments{-1};
    FuncParam function{nullptr};
    double value{-1};

};
}