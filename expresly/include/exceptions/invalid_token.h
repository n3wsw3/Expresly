#pragma once
#include <exception>
#include <string>
#include <sstream>

namespace expresly {
class invalid_token : public std::exception {
 public:
  invalid_token(const std::string& token) : m_Token(token) {}

  const char* what() const throw() { 
		return  "Invalid Token in Expression"; 
	}

	const std::string& token_name() const {
		return m_Token;
	}

 private:
  std::string m_Token;
};
}  // namespace expresly