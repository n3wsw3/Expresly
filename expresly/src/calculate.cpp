#include "calculate.h"

#include <algorithm>

namespace Expresly {
double Calculate::EvaluateRPN(std::queue<Token> queue) {
  std::stack<Token> stack;
  while (!queue.empty()) {
    Token t = queue.front();
    queue.pop();
    if (t.type == Token::Type::Function) {
      std::vector<double> v;
      v.reserve(t.arguments);
      for (int i = 0; i < t.arguments; i++) {
        v.push_back(stack.top().value);
        stack.pop();
      }
      stack.push(Token{Token::Type::Number, std::to_string(t.function(v))});
    } else if (t.type == Token::Type::Operator) {
      std::vector<double> v;
      v.reserve(2);
      v.push_back(stack.top().value);
      stack.pop();
      v.push_back(stack.top().value);
      stack.pop();
      std::reverse(v.begin(), v.end());
      stack.push(Token{Token::Type::Number, std::to_string(t.function(v))});
    } else {
      stack.push(t);
    }
  }
  return stack.top().value;
}

std::queue<Token> Calculate::ExpressionToRPN(std::vector<Token> tokens) {
  std::queue<Token> queue;
  std::stack<Token> stack;
  std::stack<bool> were;
  std::stack<int> args;

  for (auto& token : tokens) {
    switch (token.type) {
      case Token::Type::Number: {
        queue.push(token);
        if (!were.empty()) {
          were.pop();
          were.push(true);
        }
      } break;
      case Token::Type::Function: {
        stack.push(token);
        args.push(0);
        if (!were.empty()) {
          were.pop();
          were.push(true);
        }
        were.push(false);
      } break;
      case Token::Type::FunctionDelimiter: {
        while (stack.top().type != Token::Type::LeftParam) {
          queue.push(stack.top());
          stack.pop();
        }
        bool w = were.top();
        if (w) {
          args.top()++;
          were.top() = false;
        }
      } break;
      case Token::Type::Operator: {
        while (!stack.empty()) {
          if (((token.precedence <= stack.top().precedence) &&
               !token.rightAssociative) ||
              (token.rightAssociative &&
               token.precedence < stack.top().precedence)) {
            queue.push(stack.top());
            stack.pop();
          } else {
            break;
          }
        }
        stack.push(token);
      } break;
      case Token::Type::LeftParam: {
        stack.push(token);
      } break;
      case Token::Type::RightParam: {
        while (stack.top().type != Token::Type::LeftParam) {
          queue.push(stack.top());
          stack.pop();
        }
        stack.pop();
        if (!stack.empty() && stack.top().type == Token::Type::Function) {
          Token f = stack.top();
          stack.pop();
          int a = args.top();
          args.pop();
          bool w = were.top();
          were.pop();
          if (w) {
            a++;
          }
          f.arguments = a;
          queue.push(f);
        }
      } break;
      case Token::Type::Unknown:
        throw "Token is unknown";
        break;
    }
  }
  while (!stack.empty()) {
    queue.push(stack.top());
    stack.pop();
  }

  return queue;
}

bool isNumberCharacter(std::string c) {
  return (c[0] - '0' >= 0 && c[0] - '0' <= 9);
}

std::vector<Token> Calculate::ExpressionToTokens(std::string expr,
                                                 Options options = Options()) {
  std::vector<Token> tokens;
  for (std::size_t i = 0; i < expr.length(); i++) {
    // char x = expr[i];
    std::string c = expr.substr(i, 1);
    if (c == " ") continue;

    if ((c == "-" &&
         ((!tokens.empty() && (tokens.back().type == Token::Type::Operator ||
                               tokens.back().type == Token::Type::LeftParam)) ||
          tokens.empty())) ||
        c == "." || isNumberCharacter(c)) {
      while (isNumberCharacter(expr.substr(i + 1, 1)) || expr[i + 1] == '.') {
        c += expr[++i];
      }
      tokens.push_back({Token::Type::Number, c});
    } else {
      // while c is not an operator
      while (!options.isToken(c)) {
        c += expr[++i];
      }
      tokens.push_back(options.getToken(c));
    }
  }
  return tokens;
}
}  // namespace Expresly