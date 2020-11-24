#pragma once
#include <queue>
#include <stack>
#include <string>
#include "token.h"
#include "options.h"

namespace Expresly {
class Calculate
{
  private:
    Calculate() {}

  public:
    static double yeet()
    {
        return 4.0f;
    }
    ///<summary>
    /// Converts the order of a normal expression (ex. 2+2) to Reverse Polish Notation (ex. 22+)
    ///</summary>
    static std::queue<Token> ExpressionToRPN(std::vector<Token>);

    static std::queue<Token> ExpressionToRPN(std::string expression, Options options = Options())
    {
        return ExpressionToRPN(ExpressionToTokens(expression, options));
    }

    static std::vector<Token> ExpressionToTokens(std::string, Options);
    //static std::vector<Token> ExpressionToTokens( std::string expression) {
    //    return Expresly::Calculate::ExpressionToTokens(expression, Options());
    //}

    static double EvaluateRPN(std::queue<Token>);

    static double EvaluateExpression(std::vector<Token> tokens)
    {
        return EvaluateRPN(ExpressionToRPN(tokens));
    }
    ///<param name="expression">The expression that is evaluated</param>
    ///<param name="options">The options used to parse the tokens. It's default value is a normal options</param>
    ///<returns>The evaluated value</returns>
    static double EvaluateExpression(std::string expression, Options options = Options())
    {
        return EvaluateExpression(ExpressionToTokens(expression, options));
    }
};
} // namespace Expresly