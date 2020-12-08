#include <numeric>
#include <cmath>

#include "exceptions/empty_expression.h"
#include "exceptions/invalid_token.h"
#include "exceptions/mismatched_paretheses.h"
#include "expresly.h"
#include "gtest/gtest.h"

TEST(ExpressionTest, Normal) {
  EXPECT_EQ(Expresly::expression::eval("1"), 1);
  EXPECT_EQ(Expresly::expression::eval("1.0"), 1);
}

TEST(ExpressionTest, SpaceBetweenTokens) {
  EXPECT_EQ(Expresly::expression::eval("1"), 1);
  EXPECT_EQ(Expresly::expression::eval("2 + 3"), 5);
  EXPECT_EQ(Expresly::expression::eval("2 * 3"), 6);
  EXPECT_EQ(Expresly::expression::eval("6 / 3"), 2);
  EXPECT_EQ(Expresly::expression::eval("2 - 3"), -1);
  EXPECT_EQ(Expresly::expression::eval("89"), 89);
}

TEST(ExpressionTest, NoSpaceBetweenTokens) {
  EXPECT_EQ(Expresly::expression::eval("2*3"), 6);
  EXPECT_EQ(Expresly::expression::eval("2+3"), 5);
  EXPECT_EQ(Expresly::expression::eval("6/3"), 2);
  EXPECT_EQ(Expresly::expression::eval("2-3"), -1);
}

TEST(ExpressionTest, LotsOfSpaces) {
  EXPECT_EQ(Expresly::expression::eval("     2      +  3    "), 5);
  EXPECT_EQ(Expresly::expression::eval("        2*         3"), 6);
  EXPECT_EQ(Expresly::expression::eval("6             /3    "), 2);
  EXPECT_EQ(Expresly::expression::eval("       2-3          "), -1);
}

TEST(ExpressionTest, Parentheses) {
  EXPECT_EQ(Expresly::expression::eval("(2)"), 2);
  EXPECT_EQ(Expresly::expression::eval("(-1)"), -1);
  EXPECT_EQ(Expresly::expression::eval("((((2))))"), 2);
  EXPECT_EQ(Expresly::expression::eval("((2) + 4)*((5))"), 30);
}

TEST(ExpressionTest, OrderOfOperation) {
  EXPECT_EQ(Expresly::expression::eval("2^2^3"), 256);
  EXPECT_EQ(Expresly::expression::eval("2^3^2"), 512);
  EXPECT_EQ(Expresly::expression::eval("2+2*2"), 6);
  EXPECT_EQ(Expresly::expression::eval("(2+2)*2"), 8);
}

TEST(ExpressionTest, NegativeSigns) {
  EXPECT_EQ(Expresly::expression::eval("-1+1"), 0);
  EXPECT_EQ(Expresly::expression::eval("-1--1"), 0);
  EXPECT_EQ(Expresly::expression::eval("1+-1"), 0);
  EXPECT_EQ(Expresly::expression::eval("1+(-1+1)"), 1);
}

TEST(ExpressionTest, MultiplyWithParentheses) {
  EXPECT_EQ(Expresly::expression::eval("-1*(1*2)"), -2);
  EXPECT_EQ(Expresly::expression::eval("(1*2)*-1"), -2);
}

TEST(ExpressionTest, JustNumber) {
  EXPECT_EQ(Expresly::expression::eval("69"), 69);
  EXPECT_EQ(Expresly::expression::eval("420"), 420);
}

TEST(ExpressionTest, DecimalNumbers) {
  EXPECT_DOUBLE_EQ(Expresly::expression::eval("69.5"), 69.5);
  EXPECT_DOUBLE_EQ(Expresly::expression::eval("420.3"), 420.3);
  EXPECT_DOUBLE_EQ(Expresly::expression::eval("69.69"), 69.69);

  EXPECT_EQ(Expresly::expression::eval("4*2.5 + 8.5+1.5 / 3.0"), 19);
  EXPECT_DOUBLE_EQ(Expresly::expression::eval("5.0005 + 0.0095"), 5.01);
}

TEST(ExpressionTest, NegativeNumbers) {
  EXPECT_EQ(Expresly::expression::eval("-69"), -69);
  EXPECT_EQ(Expresly::expression::eval("-420"), -420);
  EXPECT_DOUBLE_EQ(Expresly::expression::eval("-0.420"), -0.420);
}

TEST(ExpressionTest, InvalidToken) {
  // Should raise wrong token
  EXPECT_THROW(Expresly::expression::eval("6 + c"), Expresly::invalid_token);
  EXPECT_THROW(Expresly::expression::eval("7 & 2"), Expresly::invalid_token);
  EXPECT_THROW(Expresly::expression::eval(" %"), Expresly::invalid_token);
}

TEST(ExpressionTest, EmptyExpression) {
  // Should raise empty expression
  EXPECT_THROW(Expresly::expression::eval(""), Expresly::empty_expression);
  // Spaces
  EXPECT_THROW(Expresly::expression::eval(" "), Expresly::empty_expression);
  // Tabs
  EXPECT_THROW(Expresly::expression::eval("\t"), Expresly::empty_expression);
  // Vertical Tab
  EXPECT_THROW(Expresly::expression::eval("\v"), Expresly::empty_expression);
  // Newline
  EXPECT_THROW(Expresly::expression::eval("\n"), Expresly::empty_expression);
  // Formfeed
  EXPECT_THROW(Expresly::expression::eval("\f"), Expresly::empty_expression);
  // Carriage Return
  EXPECT_THROW(Expresly::expression::eval("\r"), Expresly::empty_expression);
}

TEST(ExpressionTest, UnbalancedParentheses) {
  // Should raise unbalanced parentheses
  EXPECT_THROW(Expresly::expression::eval("2 + (5 * 2"),
               Expresly::mismatched_parentheses);
  EXPECT_THROW(Expresly::expression::eval("2 + 5 * 2)"),
               Expresly::mismatched_parentheses);
  EXPECT_THROW(Expresly::expression::eval("(((((4))))"),
               Expresly::mismatched_parentheses);
  EXPECT_THROW(Expresly::expression::eval("((2)) * ((3"),
               Expresly::mismatched_parentheses);
  EXPECT_THROW(Expresly::expression::eval("((9)) * ((1)"),
               Expresly::mismatched_parentheses);
}

TEST(ExpressionTest, CustomFunctions) {
  Expresly::Options op = Expresly::Options();
  op.addFunction("yeet", [](std::vector<double> input) { return input[0]; });
  EXPECT_EQ(Expresly::expression::eval("1+yeet(1)", op), 2);
}

TEST(ExpressionTest, Examples) {
  Expresly::Options op = Expresly::Options();
  op.addFunction("mod", [](std::vector<double> v) {
		return std::fmod(v[1], v[0]);
  });

  EXPECT_EQ(Expresly::expression::eval("mod ( 2 + 3 , 2 )", op), 1);

  EXPECT_EQ(Expresly::expression::eval("(2 + 2)"), 4);
}

TEST(ExpressionTest, ExpressionInstance) {
  Expresly::expression ex(" 1+ 2 ");
  EXPECT_EQ(ex.eval(), 3);
  auto exp = ex.parseAsString();
  std::string expression =
      std::accumulate(exp.begin(), exp.end(), std::string{});

	EXPECT_EQ(expression, "1+2");
}