#include "expresly.h"

#include "gtest/gtest.h"

TEST(ExpreslyTest, SpaceBetweenTokens) {
  EXPECT_EQ(Expresly::Calculate::EvaluateExpression("1"), 1);
  EXPECT_EQ(Expresly::Calculate::EvaluateExpression("2 + 3"), 5);
  EXPECT_EQ(Expresly::Calculate::EvaluateExpression("2 * 3"), 6);
  EXPECT_EQ(Expresly::Calculate::EvaluateExpression("6 / 3"), 2);
  EXPECT_EQ(Expresly::Calculate::EvaluateExpression("2 - 3"), -1);
  EXPECT_EQ(Expresly::Calculate::EvaluateExpression("89"), 89);
}

TEST(ExpreslyTest, NoSpaceBetweenTokens) {
  EXPECT_EQ(Expresly::Calculate::EvaluateExpression("2+3"), 5);
  EXPECT_EQ(Expresly::Calculate::EvaluateExpression("2*3"), 6);
  EXPECT_EQ(Expresly::Calculate::EvaluateExpression("6/3"), 2);
  EXPECT_EQ(Expresly::Calculate::EvaluateExpression("2-3"), -1);
}

TEST(ExpreslyTest, LotsOfSpaces) {
  EXPECT_EQ(Expresly::Calculate::EvaluateExpression("     2      +  3    "), 5);
  EXPECT_EQ(Expresly::Calculate::EvaluateExpression("        2*         3"), 6);
  EXPECT_EQ(Expresly::Calculate::EvaluateExpression("6             /3    "), 2);
  EXPECT_EQ(Expresly::Calculate::EvaluateExpression("       2-3          "),
            -1);
}

TEST(ExpreslyTest, Parentheses) {
  EXPECT_EQ(Expresly::Calculate::EvaluateExpression("(2)"), 2);
  EXPECT_EQ(Expresly::Calculate::EvaluateExpression("(-1)"), -1);
  EXPECT_EQ(Expresly::Calculate::EvaluateExpression("((((2))))"), 2);
  EXPECT_EQ(Expresly::Calculate::EvaluateExpression("((2) + 4)*((5))"), 30);
}

TEST(ExpreslyTest, OrderOfOperation) {
  EXPECT_EQ(Expresly::Calculate::EvaluateExpression("2^2^3"), 256);
  EXPECT_EQ(Expresly::Calculate::EvaluateExpression("2^3^2"), 512);
  EXPECT_EQ(Expresly::Calculate::EvaluateExpression("2+2*2"), 6);
  EXPECT_EQ(Expresly::Calculate::EvaluateExpression("(2+2)*2"), 8);
}

TEST(ExpreslyTest, NegativeSigns) {
  EXPECT_EQ(Expresly::Calculate::EvaluateExpression("-1+1"), 0);
  EXPECT_EQ(Expresly::Calculate::EvaluateExpression("-1--1"), 0);
  EXPECT_EQ(Expresly::Calculate::EvaluateExpression("1+-1"), 0);
  EXPECT_EQ(Expresly::Calculate::EvaluateExpression("1+(-1+1)"), 1);
}

TEST(ExpreslyTest, MultiplyWithParentheses) {
  EXPECT_EQ(Expresly::Calculate::EvaluateExpression("-1*(1*2)"), -2);
  EXPECT_EQ(Expresly::Calculate::EvaluateExpression("(1*2)*-1"), -2);
}

TEST(ExpreslyTest, JustNumber) {
  EXPECT_EQ(Expresly::Calculate::EvaluateExpression("69"), 69);
  EXPECT_EQ(Expresly::Calculate::EvaluateExpression("420"), 420);
}

TEST(ExpreslyTest, DecimalNumbers) {
  EXPECT_DOUBLE_EQ(Expresly::Calculate::EvaluateExpression("69.5"), 69.5);
  EXPECT_DOUBLE_EQ(Expresly::Calculate::EvaluateExpression("420.3"), 420.3);
  EXPECT_DOUBLE_EQ(Expresly::Calculate::EvaluateExpression("69.69"), 69.69);

  EXPECT_EQ(Expresly::Calculate::EvaluateExpression("4*2.5 + 8.5+1.5 / 3.0"), 19);
  EXPECT_DOUBLE_EQ(Expresly::Calculate::EvaluateExpression("5.0005 + 0.0095"), 5.01);
}

TEST(ExpreslyTest, NegativeNumbers) {
  EXPECT_EQ(Expresly::Calculate::EvaluateExpression("-69"), -69);
  EXPECT_EQ(Expresly::Calculate::EvaluateExpression("-420"), -420);
  EXPECT_DOUBLE_EQ(Expresly::Calculate::EvaluateExpression("-.420"), -.420);
}

//TEST(ExpreslyTest, SyntaxErrors) {
//
//	// TODO: Change these to actual specific thrown errors instead of any error.
//	// Using possibly EXPECT_THROW
//
//	// Should raise wrong token
//	EXPECT_ANY_THROW(Expresly::Calculate::EvaluateExpression("  6 + c"));
//
//	// Should raise wrong operator
//	EXPECT_ANY_THROW(Expresly::Calculate::EvaluateExpression("  7 & 2"));
//
//	// Should raise wrong operand
//	EXPECT_ANY_THROW(Expresly::Calculate::EvaluateExpression(" %"));
//
//	// Should raise unbalanced parenthesis
//	EXPECT_ANY_THROW(Expresly::Calculate::EvaluateExpression("2 + (5 * 2"));
//	EXPECT_ANY_THROW(Expresly::Calculate::EvaluateExpression("(((((4))))"));
//	EXPECT_ANY_THROW(Expresly::Calculate::EvaluateExpression("((2)) * ((3"));
//	EXPECT_ANY_THROW(Expresly::Calculate::EvaluateExpression("((9)) * ((1)"));
//
//	// Should raise empty expression
//	EXPECT_ANY_THROW(Expresly::Calculate::EvaluateExpression(""));
//	EXPECT_ANY_THROW(Expresly::Calculate::EvaluateExpression("  "));
//}

TEST(ExpreslyTest, CustomFunctions) {
  Expresly::Options op = Expresly::Options();
  op.addFunction("yeet", [](std::vector<double> input) { return input[0]; });
  EXPECT_EQ(Expresly::Calculate::EvaluateExpression("1+yeet(1)", op), 2);
}

TEST(ExpreslyTest, Examples) {
  Expresly::Options op = Expresly::Options();
  op.addFunction("mod", [](std::vector<double> v) {
    return static_cast<double>(
        (static_cast<int>(v[1]) % static_cast<int>(v[0])));
  });

  EXPECT_EQ(Expresly::Calculate::EvaluateExpression("mod ( 2 + 3 , 2 )", op),
            1);
}