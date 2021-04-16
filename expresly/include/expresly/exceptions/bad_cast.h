#pragma once
#include <typeinfo>
#include <string>

namespace expresly {
class bad_cast : public std::bad_cast {
 private:
	 std::string message;
 public:

	bad_cast(const std::string& message) : message{message} {}
  const char* what() const throw() { return message.c_str(); }
};
}  // namespace expresly