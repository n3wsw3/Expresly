#include "options.h"

#include <cmath>

namespace Expresly {

Options::Options() { populateOperators(); }
void Options::addOperator(std::string string, int precedence,
                          bool rightHandAssociative, FuncParam func) {
  operators.insert({string, Token{Token::Type::Operator, string, precedence,
                                  rightHandAssociative, func}});
}
void Options::addFunction(std::string string, FuncParam func) {
  operators.insert(
      {string, Token{Token::Type::Function, string, -1, false, func}});
}
void Options::populateOperators() {
  operators.insert({"(", Token{Token::Type::LeftParam, ")"}});
  operators.insert({")", Token{Token::Type::RightParam, ")"}});
  addOperator("^", 4, true,
              [](std::vector<double> v) { return std::pow(v[0], v[1]); });
  addOperator("*", 3, false, [](std::vector<double> v) {
    double val = v[0];
    for (std::size_t i = 1; i < v.size(); i++) {
      val *= v[i];
    }
    return val;
  });
  addOperator("/", 3, false, [](std::vector<double> v) {
    double val = v[0];
    for (std::size_t i = 1; i < v.size(); i++) {
      val /= v[i];
    }
    return val;
  });
  addOperator("+", 2, false, [](std::vector<double> v) {
    double val = 0;
    for (auto& d : v) {
      val += d;
    }
    return val;
  });
  addOperator("-", 2, false, [](std::vector<double> v) {
    double val = v[0];
    for (std::size_t i = 1; i < v.size(); i++) {
      val -= v[i];
    }
    return val;
  });
  operators.insert({",", Token{Token::Type::FunctionDelimiter, ","}});
  addFunction("sum", [](std::vector<double> v) {
    double val = 0;
    for (auto& d : v) {
      val += d;
    }
    return val;
  });
}
bool Options::isOperator(std::string str) {
  return !(operators.find(str) == operators.end());
}
}  // namespace Expresly