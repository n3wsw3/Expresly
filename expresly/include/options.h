#pragma once
#include <map>
#include <string>

#include "token.h"
#include "types.h"

namespace expresly {
class Options {
 public:
  Options();
  Options(std::map<std::string, Token>);

  void addOperator(const std::string&, int, bool, FuncParam);
  void addFunction(const std::string&, FuncParam);

  bool isToken(const std::string&);
	Token getToken(const std::string&);

 private:
  void populateOperators();

 private:
  std::map<std::string, Token> tokens;
};
}  // namespace expresly