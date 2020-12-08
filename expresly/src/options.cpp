#include "options.h"
#include "exceptions/invalid_token.h"

#include <cmath>

namespace Expresly {

Options::Options() { populateOperators(); }

Options::Options(std::map<std::string, Token> op) : Options() {
  tokens.insert(op.begin(), op.end());
}

void Options::addOperator(const std::string& string, int precedence,
                          bool rightHandAssociative, FuncParam func) {
  tokens.insert({string, Token{Token::Type::Operator, string, precedence,
                               rightHandAssociative, func}});
}
void Options::addFunction(const std::string& string, FuncParam func) {
  tokens.insert(
      {string, Token{Token::Type::Function, string, -1, false, func}});
}

void Options::populateOperators() {
  tokens.insert({"(", Token{Token::Type::LeftParam, "("}});
  tokens.insert({")", Token{Token::Type::RightParam, ")"}});
  tokens.insert({",", Token{Token::Type::FunctionDelimiter, ","}});

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
  addFunction("sum", [](std::vector<double> v) {
    double val = 0;
    for (auto& d : v) {
      val += d;
    }
    return val;
  });
}
bool Options::isToken(const std::string& str) {
  return !(tokens.find(str) == tokens.end());
}

Token Options::getToken(const std::string& str) {
	//if (isToken(str))
		return tokens[str];
	//throw invalid_token(str);
}
}  // namespace Expresly