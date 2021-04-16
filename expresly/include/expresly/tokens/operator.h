#pragma once
#include <functional>
#include <memory>

#include "token.h"

namespace expresly {
class token_operator : public token {
  token_operator(const std::string& _name, token_type _type)
      : token{_name, _type} {}

  const virtual std::shared_ptr<token> execute(
      std::span<std::shared_ptr<token>> el) const = 0;
};
}  // namespace expresly
