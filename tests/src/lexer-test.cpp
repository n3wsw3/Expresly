#include "gtest/gtest.h"

#include "expresly/lexer.h"

TEST(Lexer, Expression) {
  auto exp = "1.0+ -1 - pow(2, 2) =2";
  auto lex = expresly::Lexer(exp);
  for (auto token = lex.next();
    not token.is_one_of(expresly::Lexer::Token::Type::End, expresly::Lexer::Token::Type::Unexpected);
    token = lex.next()) {
    std::cout << std::setw(12) << token.type() << " |" << token.lexeme()
      << "|\n";
  }
}