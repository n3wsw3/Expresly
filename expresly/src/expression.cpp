#include "expression.h"

#include <algorithm>
#include <cctype>
#include <queue>

#include "exceptions/empty_expression.h"
#include "exceptions/invalid_token.h"
#include "exceptions/mismatched_paretheses.h"

namespace expresly {
expression::expression(const std::string& expression)
    : m_Original{expression} {}
expression::expression(std::string&& expression)
    : m_Original{std::move(expression)} {}

const std::regex expression::s_NumRegex{"-?[0-9]+([\\.][0-9]+)?"};

// Checks whether a string is a valid double
bool expression::isnumber(const std::string& num) {
  return std::regex_match(num, s_NumRegex);
}

std::vector<Token> expression::parse(const std::string& expression) {
  return parse(expression, Options());
}

// Will convert an expression into a vector of tokens.
// Does NOT guarantee the expression is valid.
std::vector<Token> expression::parse(const std::string& expression,
                                     Options options) {
  // If the expression only contains spaces
  // if (expression.find_first_not_of(' ') == std::string::npos)
  if (std::all_of(expression.begin(), expression.end(), isspace))
    throw empty_expression();

  std::vector<Token> tokens;
  for (std::size_t i = 0; i < expression.length(); i++) {
    // If the next character is a space just ignore it
    if (expression[i] == ' ') continue;

    // Initialize the beginning of the next token to the character at the ith
    // Index
    std::string c = {expression[i]};
    // If c is a negative sign and is directly after an operator ("5 + -4"),
    // after a left parentheses ("5 + (-4+5)"), or if it's the first token
    // ("-4+5"). Or the character is a number
    // character ("0.45 + 5" or "-0.45"). Then this is the start of a number
    if ((c == "-" &&
         ((!tokens.empty() && (tokens.back().type == Token::Type::Operator ||
                               tokens.back().type == Token::Type::LeftParam)) ||
          tokens.empty())) ||
        std::isdigit(expression[i])) {
      // While the next character in the expression is a number character or a
      // decimal point. This does not check for if there is multiple decimal
      // points though. Thus it might fail when being parsed as a Token.
      while (std::isdigit(expression[i + 1]) || expression[i + 1] == '.') {
        c += expression[++i];
      }

      // Check if c is actually a number.
      // Since right now c can contain more than one decimal point.
      if (!isnumber(c)) throw invalid_token(c);

      tokens.push_back({Token::Type::Number, c});
    } else {
      // This is guaranteed to be a function, operator, function delimiter,
      // parentheses, or a synatax error.
      // Loops and appends until c is a token or until the end of the expression
      // is reached.
      while (!options.isToken(c) && i < expression.length() - 1) {
        c += expression[++i];
      }
      // Check if c is actually the name of a token.
      // Since the while loop above will continue on until it is a valid token,
      // it means c can either be a valid token or the rest of the expression.
      if (!options.isToken(c)) {
        throw invalid_token(c);
      }
      // Here it is guaranteed c is a valid token.
      tokens.push_back(options.getToken(c));
    }
  }
  return tokens;
}

std::vector<std::string> expression::parseAsString(
    const std::string& expression) {
  return parseAsString(expression, Options());
}

std::vector<std::string> expression::parseAsString(
    const std::string& expression, Options options) {
  auto tokens = parse(expression, options);
  // Set the size of string tokens to the size of tokens.
  std::vector<std::string> string_tokens(tokens.size());
  // Set string_tokens to the string variable of every token.
  std::transform(tokens.begin(), tokens.end(), string_tokens.begin(),
                 [](Token& el) { return el.string; });

  return string_tokens;
}

std::queue<Token> expression::asRPN(const std::string& expression) {
  return asRPN(expression, Options());
}

std::queue<Token> expression::asRPN(const std::string& expression,
                                    Options options) {
  return asRPN(parse(expression, options));
}

std::queue<Token> expression::asRPN(const std::vector<Token>& tokens) {
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
        while (!stack.empty() && stack.top().type != Token::Type::LeftParam) {
          queue.push(stack.top());
          stack.pop();
        }

        if (stack.empty()) throw mismatched_parentheses();

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
        throw invalid_token("Unknown");
        break;
    }
  }
  while (!stack.empty()) {
    if (stack.top().type == Token::Type::LeftParam)
      throw mismatched_parentheses();
    queue.push(stack.top());
    stack.pop();
  }

  return queue;
}

double expression::eval(const std::string& expression) {
  return eval(expression, Options());
}

double expression::eval(const std::string& expression, Options options) {
  return eval(parse(expression, options));
}

double expression::eval(const std::vector<Token>& tokens) {
  return eval(asRPN(tokens));
}

double expression::eval(std::queue<Token> queue) {
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

std::vector<Token> expression::parse() { return expression::parse(m_Original); }

std::vector<Token> expression::parse(Options options) {
  return expression::parse(m_Original, options);
}

std::vector<std::string> expression::parseAsString() {
  return expression::parseAsString(m_Original);
}

std::vector<std::string> expression::parseAsString(Options options) {
  return expression::parseAsString(m_Original, options);
}

std::queue<Token> expression::asRPN() {
	return expression::asRPN(m_Original);
}

std::queue<Token> expression::asRPN(Options options) {
	return expression::asRPN(m_Original, options);
}

double expression::eval() {
	return expression::eval(m_Original);
}

double expression::eval(Options options) {
	return expression::eval(m_Original, options);
}

}  // namespace expresly