#include "expresly/tokens/number.h"
#include "expresly/tokens/token.h"
#include "gtest/gtest.h"

expresly::token_number n1{1};
expresly::token_number n2{1.2};
expresly::token_number n3{1.2f};

TEST(NumberTest, ImplicitCast) {
  EXPECT_EQ(n1, 1);
  EXPECT_EQ(n2, 1.2);
  EXPECT_EQ(n3, 1.2f);
}

TEST(NumberTest, Types) {
  expresly::token_number n4 = n1 + n2 + n3;

  EXPECT_EQ(n1.type, expresly::token_type::Integer);
  EXPECT_EQ(n2.type, expresly::token_type::Decimal);
  EXPECT_EQ(n3.type, expresly::token_type::Decimal);

  EXPECT_EQ((n1 + n2 + n3).type, expresly::token_type::Decimal);
  EXPECT_EQ((n2 + n1 + n3).type, expresly::token_type::Decimal);

  EXPECT_EQ((n1 + n1).type, expresly::token_type::Integer);
  EXPECT_EQ((n2 + n2).type, expresly::token_type::Decimal);
  EXPECT_EQ((n3 + n3).type, expresly::token_type::Decimal);

  EXPECT_EQ(n4.type, expresly::token_type::Decimal);
}

TEST(NumberTest, Addition) {
  EXPECT_FLOAT_EQ(n1 + n2 + n3, 3.4);
  EXPECT_FLOAT_EQ(n2 + n1 + n3, 3.4);

  EXPECT_EQ(n1 + n1, 2);
  EXPECT_DOUBLE_EQ(n2 + n2, 2.4);
  EXPECT_FLOAT_EQ(n3 + n3, 2.4);
}

TEST(NumberTest, Multiplication) {
  EXPECT_EQ(n1 * expresly::token_number{2}, 2);

  EXPECT_FLOAT_EQ((n1 * n2 * n3), 1.44);
  EXPECT_FLOAT_EQ((n2 * n1 * n3), 1.44);

  EXPECT_EQ(n1 * n1, 1);
  EXPECT_DOUBLE_EQ(n2 * n2, 1.44);
  EXPECT_FLOAT_EQ(n3 * n3, 1.44);
}

TEST(NumberTest, Division) {

	n1 += expresly::token_number{2};
	n1 -= 2;

  EXPECT_DOUBLE_EQ(n1 / expresly::token_number{2}, 0.5);
  EXPECT_EQ(expresly::token_number{4} / expresly::token_number{2}, 2);

  EXPECT_FLOAT_EQ((n1 / n2 / n3), 1 / 1.2 / 1.2);
  EXPECT_FLOAT_EQ((n2 / n1 / n3), 1.2 / 1 / 1.2);

  EXPECT_EQ(n1 * n1, 1);
  EXPECT_DOUBLE_EQ(n2 * n2, 1.44);
  EXPECT_FLOAT_EQ(n3 * n3, 1.44);
}

TEST(NumberTest, Boolean) {
	auto x = expresly::token_number{true};
	auto y = expresly::token_number{1};

	expresly::token* z = &y;

	//z->asInteger()
	auto h1 = dynamic_cast<expresly::token_number<int>*>(z);
	auto h2 = z->As<expresly::token_number<int>>();

	EXPECT_EQ(h1->value, 1);
	EXPECT_EQ(h2->value, 1);
	EXPECT_EQ(z->As<expresly::token_number<int>>()->value, 1);
	EXPECT_EQ(z->asInteger()., 1);

	EXPECT_EQ(x.type, expresly::token_type::Boolean);
	EXPECT_EQ(x+y, 2);
}