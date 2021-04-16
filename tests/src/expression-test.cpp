#include <array>
#include <cmath>
#include <iostream>
#include <numeric>
#include <tuple>
#include <unordered_map>
#include <utility>

#include "expresly.h"
#include "gtest/gtest.h"

TEST(ExpressionTest, Normal) {
  EXPECT_EQ(expresly::expression::eval("1"), 1);
  EXPECT_EQ(expresly::expression::eval("1.0"), 1);
  EXPECT_EQ(expresly::expression::eval("(-2+(2^2-4*-1*3)^(1/2))/(2*-1)"), -1);
}

TEST(ExpressionTest, SpaceBetweenTokens) {
  EXPECT_EQ(expresly::expression::eval("1"), 1);
  EXPECT_EQ(expresly::expression::eval("2 + 3"), 5);
  EXPECT_EQ(expresly::expression::eval("2 * 3"), 6);
  EXPECT_EQ(expresly::expression::eval("6 / 3"), 2);
  EXPECT_EQ(expresly::expression::eval("2 - 3"), -1);
  EXPECT_EQ(expresly::expression::eval("89"), 89);
}

TEST(ExpressionTest, NoSpaceBetweenTokens) {
  EXPECT_EQ(expresly::expression::eval("2*3"), 6);
  EXPECT_EQ(expresly::expression::eval("2+3"), 5);
  EXPECT_EQ(expresly::expression::eval("6/3"), 2);
  EXPECT_EQ(expresly::expression::eval("2-3"), -1);
}

TEST(ExpressionTest, LotsOfSpaces) {
  EXPECT_EQ(expresly::expression::eval("     2      +  3    "), 5);
  EXPECT_EQ(expresly::expression::eval("        2*         3"), 6);
  EXPECT_EQ(expresly::expression::eval("6             /3    "), 2);
  EXPECT_EQ(
      expresly::expression::eval("       2-3				    "),
      -1);
}

TEST(ExpressionTest, Parentheses) {
  EXPECT_EQ(expresly::expression::eval("(2)"), 2);
  EXPECT_EQ(expresly::expression::eval("(-1)"), -1);
  EXPECT_EQ(expresly::expression::eval("((((2))))"), 2);
  EXPECT_EQ(expresly::expression::eval("((2) + 4)*((5))"), 30);
}

TEST(ExpressionTest, OrderOfOperation) {
  EXPECT_EQ(expresly::expression::eval("2^2^3"), 256);
  EXPECT_EQ(expresly::expression::eval("2^3^2"), 512);
  EXPECT_EQ(expresly::expression::eval("2+2*2"), 6);
  EXPECT_EQ(expresly::expression::eval("(2+2)*2"), 8);
}

TEST(ExpressionTest, NegativeSigns) {
  EXPECT_EQ(expresly::expression::eval("-1+1"), 0);
  EXPECT_EQ(expresly::expression::eval("-1--1"), 0);
  EXPECT_EQ(expresly::expression::eval("1+-1"), 0);
  EXPECT_EQ(expresly::expression::eval("1+(-1+1)"), 1);
}

TEST(ExpressionTest, MultiplyWithParentheses) {
  EXPECT_EQ(expresly::expression::eval("-1*(1*2)"), -2);
  EXPECT_EQ(expresly::expression::eval("(1*2)*-1"), -2);
}

TEST(ExpressionTest, JustNumber) {
  EXPECT_EQ(expresly::expression::eval("69"), 69);
  EXPECT_EQ(expresly::expression::eval("420"), 420);
}

// Creating an array compile time without having to specify the size of the
// array as a template argument. Creates the same behavior as "int arr[] =
// {...}" but using c++ std arrays. This should be built-in.
template <typename... T>
constexpr auto make_array(T&&... t) {
  return std::array{static_cast<std::common_type_t<T...>>(t)...};
}

TEST(ExpressionTest, DecimalNumbers) {
  // Test to make sure it can handle all different types of formats a number can
  // be in. Both negative and positive, starting just a period for decimals,
  // starting with a 0, starting with any number, any number and then a period.
  // The whole thing.
  using TestCase = std::pair<std::string, double>;
  const auto tests = make_array(
      TestCase{"9", 9}, TestCase{"0", 0}, TestCase{"10", 10},
      TestCase{"10.", 10.}, TestCase{"0.", 0.}, TestCase{"0.0", 0.0},
      TestCase{"0.100", 0.100}, TestCase{"0.10", 0.10}, TestCase{"0.01", 0.01},
      TestCase{"10.0", 10.0}, TestCase{"10.10", 10.10}, TestCase{".0", .0},
      TestCase{".1", .1}, TestCase{".00", .00}, TestCase{".100", .100},
      TestCase{".001", .001}, TestCase{"-9", -9}, TestCase{"-0", -0},
      TestCase{"-10", -10}, TestCase{"-10.", -10.}, TestCase{"-0.", -0.},
      TestCase{"-0.0", -0.0}, TestCase{"-0.100", -0.100},
      TestCase{"-0.10", -0.10}, TestCase{"-0.01", -0.01},
      TestCase{"-10.0", -10.0}, TestCase{"-10.10", -10.10},
      TestCase{"-.0", -.0}, TestCase{"-.1", -.1}, TestCase{"-.00", -.00},
      TestCase{"-.100", -.100}, TestCase{"-.001", -.001});

  for (auto& [str, num] : tests) {
    EXPECT_DOUBLE_EQ(expresly::expression::eval(str), num);
  }

  // Arithmetic with decimals
  EXPECT_EQ(expresly::expression::eval("4*2.5 + 8.5+1.5 / 3.0"), 19);
  EXPECT_DOUBLE_EQ(expresly::expression::eval("5.0005 + 0.0095"), 5.01);
}

TEST(ExpressionTest, NegativeNumbers) {
  EXPECT_EQ(expresly::expression::eval("-69"), -69);
  EXPECT_EQ(expresly::expression::eval("-420"), -420);
  EXPECT_DOUBLE_EQ(expresly::expression::eval("-0.420"), -0.420);
}

TEST(ExpressionTest, InvalidToken) {
  // Should raise wrong token
  EXPECT_THROW(expresly::expression::eval("6 + c"), expresly::invalid_token);
  EXPECT_THROW(expresly::expression::eval("7 & 2"), expresly::invalid_token);
  EXPECT_THROW(expresly::expression::eval(" %"), expresly::invalid_token);
}

TEST(ExpressionTest, EmptyExpression) {
  // Should raise empty expression
  EXPECT_THROW(expresly::expression::eval(""), expresly::empty_expression);
  // Spaces
  EXPECT_THROW(expresly::expression::eval(" "), expresly::empty_expression);
  // Tabs
  EXPECT_THROW(expresly::expression::eval("\t"), expresly::empty_expression);
  // Vertical Tab
  EXPECT_THROW(expresly::expression::eval("\v"), expresly::empty_expression);
  // Newline
  EXPECT_THROW(expresly::expression::eval("\n"), expresly::empty_expression);
  // Formfeed
  EXPECT_THROW(expresly::expression::eval("\f"), expresly::empty_expression);
  // Carriage Return
  EXPECT_THROW(expresly::expression::eval("\r"), expresly::empty_expression);
}

TEST(ExpressionTest, WhiteSpaceCharacters) {
  EXPECT_EQ(expresly::expression::eval("2 +\t 3"), 5);
  EXPECT_EQ(expresly::expression::eval("2 +\v 3"), 5);
  EXPECT_EQ(expresly::expression::eval("2 +\n 3"), 5);
  EXPECT_EQ(expresly::expression::eval("2 +\f 3"), 5);
  EXPECT_EQ(expresly::expression::eval("2 +\r 3"), 5);
}

TEST(ExpressionTest, UnbalancedParentheses) {
  // Should raise unbalanced parentheses
  EXPECT_THROW(expresly::expression::eval("2 + (5 * 2"),
               expresly::mismatched_parentheses);
  EXPECT_THROW(expresly::expression::eval("2 + 5 * 2)"),
               expresly::mismatched_parentheses);
  EXPECT_THROW(expresly::expression::eval("(((((4))))"),
               expresly::mismatched_parentheses);
  EXPECT_THROW(expresly::expression::eval("((2)) * ((3"),
               expresly::mismatched_parentheses);
  EXPECT_THROW(expresly::expression::eval("((9)) * ((1)"),
               expresly::mismatched_parentheses);
}

TEST(ExpressionTest, CustomFunctions) {
  expresly::Options op = expresly::Options();
  op.addFunction("yeet", [](std::vector<double> input) { return input[0]; });
  EXPECT_EQ(expresly::expression::eval("1+yeet(1)", op), 2);

  // Overwriting functions
  op.addFunction("yeet",
                 [](std::vector<double> input) { return input[0] + 1; });
  EXPECT_EQ(expresly::expression::eval("1+yeet(1)", op), 3);
}

TEST(ExpressionTest, IfStatement) {
  expresly::Options op = expresly::Options();

  op.addFunction("if",
                 [](std::vector<double> v) { return v[0] > 0 ? v[1] : v[2]; });

  EXPECT_EQ(expresly::expression::eval("if(-5, 1, 0)", op), 0);

  EXPECT_EQ(expresly::expression::eval("if(5+5, 1, 0)", op), 1);
}

TEST(ExpressionTest, Examples) {
  expresly::Options op = expresly::Options();
  op.addFunction("mod",
                 [](std::vector<double> v) { return std::fmod(v[0], v[1]); });

  EXPECT_EQ(expresly::expression::eval("mod ( 2 + 3 , 2 )", op), 1);

  EXPECT_EQ(expresly::expression::eval("(2 + 2)"), 4);
}

TEST(ExpressionTest, ExpressionInstance) {
  std::string str(" 1+\t2");
  expresly::expression ex(str);
  EXPECT_EQ(ex.eval(), 3);
  auto exp = ex.parseAsString();
  std::string expression =
      std::accumulate(exp.begin(), exp.end(), std::string{});

  EXPECT_EQ(expression, "1+2");
}

TEST(ExpressionTest, FutureTests) {
  // Should throw missing operand exeption
  // EXPECT_ANY_THROW(expresly::expression::eval("2+"));

  // Implicit multiplication
  EXPECT_EQ(expresly::expression::eval("2(2)"), 4);
}