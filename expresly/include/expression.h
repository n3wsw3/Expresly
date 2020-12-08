#include <regex>
#include <string>
#include <utility>
#include <variant>
#include <vector>
#include <queue>
#include <stack>

#include "options.h"
#include "token.h"

namespace expresly {
class expression {
 public:
  expression(const std::string&);
  expression(std::string&&);

  static std::vector<Token> parse(const std::string&);
  static std::vector<Token> parse(const std::string&, Options);
  static std::vector<std::string> parseAsString(const std::string&);
  static std::vector<std::string> parseAsString(const std::string&, Options);

	static std::queue<Token> asRPN(const std::string&);
	static std::queue<Token> asRPN(const std::string&, Options);
	static std::queue<Token> asRPN(const std::vector<Token>&);

	static double eval(const std::string&);
	static double eval(const std::string&, Options);
	static double eval(const std::vector<Token>&);
	static double eval(std::queue<Token>);

	std::vector<Token> parse();
  std::vector<Token> parse(Options);
  std::vector<std::string> parseAsString();
  std::vector<std::string> parseAsString(Options);

	std::queue<Token> asRPN();
	std::queue<Token> asRPN(Options);

	double eval();
	double eval(Options);

 private:
  static bool isnumber(const std::string&);

 private:
  std::string m_Original;

  static const std::regex s_NumRegex;
};
}  // namespace expresly