#pragma once
#include <map>
#include <string>
#include "token.h"
#include "types.h"


namespace Expresly {
class Options
{
  private:
    void populateOperators();

  public:
    std::map<std::string, Token> operators{};
    void addOperator(std::string, int, bool, FuncParam);
    void addFunction(std::string, FuncParam);

    Options();
    Options( std::map<std::string, Token> op ) {
        operators.insert(op.begin(), op.end());
        populateOperators();
    }

    bool isOperator(std::string);
};
}