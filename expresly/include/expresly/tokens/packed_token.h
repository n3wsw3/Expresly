#pragma once
#include <memory>

#include "number.h"
#include "token.h"
#include "operator.h"
#include "expresly/exceptions.h"

#include "fmt/core.h"

namespace expresly {
class packed_token {
  std::shared_ptr<token> base_token;

  packed_token(std::shared_ptr<token> base) : base_token{base} {}

  const std::shared_ptr<token_number<int>> asInteger() const {
    switch (base_token->type) {
      case token_type::Decimal:
        return std::make_shared<token_number<int>>(
            std::static_pointer_cast<token_number<double>>(base_token)->value);
      case token_type::Boolean:
        return std::make_shared<token_number<int>>(
            std::static_pointer_cast<token_number<bool>>(base_token)->value);
      case token_type::Integer:
        return std::static_pointer_cast<token_number<int>>(base_token);
      default:
        return 0;
    }
  }

  const std::shared_ptr<token_number<double>> asDecimal() const {
    switch (base_token->type) {
      case token_type::Decimal:
        return std::static_pointer_cast<token_number<double>>(base_token);
      case token_type::Boolean:
        return std::make_shared<token_number<double>>(
            std::static_pointer_cast<token_number<bool>>(base_token)->value);
      case token_type::Integer:
        return std::make_shared<token_number<double>>(
            std::static_pointer_cast<token_number<int>>(base_token)->value);
      default:
        return 0;
    }
  }

  const std::shared_ptr<token_number<bool>> asBoolean() const {
    switch (base_token->type) {
      case token_type::Decimal:
        return std::make_shared<token_number<bool>>(
            std::static_pointer_cast<token_number<double>>(base_token)->value);
      case token_type::Boolean:
        return std::static_pointer_cast<token_number<bool>>(base_token);
      case token_type::Integer:
        return std::make_shared<token_number<bool>>(
            std::static_pointer_cast<token_number<int>>(base_token)->value);
      default:
        return false;
    }
  }

	const std::shared_ptr<token_operator> asOperator() const {
		if (base_token->type == token_type::Operator)
			return std::static_pointer_cast<token_operator>(base_token);
		throw expresly::bad_cast(fmt::format("Cannot convert {} to {}", base_token->type, "Operator"));
	}

  std::shared_ptr<token> token() const { return base_token; }
};
}  // namespace expresly