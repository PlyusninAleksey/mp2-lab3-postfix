#include "Postfix.h"
#include <gtest.h>

TEST(TArithmeticExpression, can_create_empty_postfix)
{
	ASSERT_NO_THROW(TArithmeticExpression p);
}

TEST(TArithmeticExpression, can_create_definite_postfix)
{
	std::string infixExpression = "1 + 2 + 3";
	ASSERT_NO_THROW(TArithmeticExpression p(infixExpression));
}

TEST(TArithmeticExpression, can_get_postfix)
{
	std::string infixExpression = "1 + 2 + 3";
	TArithmeticExpression p(infixExpression);
	ASSERT_NO_THROW(p.getPostfix());
}

TEST(TArithmeticExpression, can_get_infix)
{
	std::string infixExpression = "1 + 2 + 3";
	TArithmeticExpression p(infixExpression);
	ASSERT_NO_THROW(p.getInfix());
}

TEST(TArithmeticExpression, is_infix_correct)
{
	std::string infixExpression = "1 + 2 + 3";
	TArithmeticExpression p(infixExpression);
	ASSERT_EQ(p.getInfix(), "1 + 2 + 3");
}

TEST(TArithmeticExpression, is_postfix_correct)
{
	std::string infixExpression = "1 + 2 + 3";
	TArithmeticExpression p(infixExpression);
	ASSERT_EQ(p.getPostfix(), "1 2 + 3 + ");
}

TEST(TArithmeticExpression, is_simple_expression_calculate_correct)
{
	std::string infixExpression = "1 + 2 + 3";
	TArithmeticExpression p(infixExpression);
	ASSERT_EQ(p.calculate(), 6);
}

TEST(TArithmeticExpression, is_brackets_operator_correct)
{
	std::string infixExpression = "2 * (2 + 3)";
	TArithmeticExpression p(infixExpression);
	ASSERT_EQ(p.calculate(), 10);
}

TEST(TArithmeticExpression, is_plus_operator_correct)
{
	std::string infixExpression = "2 + 3";
	TArithmeticExpression p(infixExpression);
	ASSERT_EQ(p.calculate(), 5);
}

TEST(TArithmeticExpression, is_div_operator_correct)
{
	std::string infixExpression = "10 / (2 + 3)";
	TArithmeticExpression p(infixExpression);
	ASSERT_EQ(p.calculate(), 2);
}

TEST(TArithmeticExpression, is_mul_operator_correct)
{
	std::string infixExpression = "2 * 2";
	TArithmeticExpression p(infixExpression);
	ASSERT_EQ(p.calculate(), 4);
}

TEST(TArithmeticExpression, is_minus_operator_correct)
{
	std::string infixExpression = "2 - 2";
	TArithmeticExpression p(infixExpression);
	ASSERT_EQ(p.calculate(), 0);
}

TEST(TArithmeticExpression, is_float_num_calculate_correct)
{
	std::string infixExpression = "1.33 + 2.67";
	TArithmeticExpression p(infixExpression);
	ASSERT_EQ(p.calculate(), 4);
}

TEST(TArithmeticExpression, is_complex_expression_calculate_correct)
{
	std::string infixExpression = "((1.33 + 2.67) / 2) * (4 + 4) - 2.5";
	TArithmeticExpression p(infixExpression);
	ASSERT_EQ(p.calculate(), 13.5);
}

TEST(TArithmeticExpression, cant_calculate_invalid_expression)
{
	std::string infixExpression = "1+";
	TArithmeticExpression p(infixExpression);
	ASSERT_ANY_THROW(p.calculate());
}

TEST(TArithmeticExpression, can_get_operands)
{
	std::string infixExpression = "1 + 2 + 3";
	TArithmeticExpression p(infixExpression);
	ASSERT_NO_THROW(p.getOperands());
}




