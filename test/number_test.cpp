#include <CppUTest/TestHarness.h>
#include <limits.h>

#include "../src/parser.h"

TEST_GROUP(parse_number)
{
};

TEST(parse_number, ReturnNumberNode)
{
    struct ast_node *num;
    num = parse_number("1");
    CHECK_EQUAL(AST_NUMBER, num->type);
}

TEST(parse_number, NoChildren)
{
    struct ast_node *num;
    num = parse_number("2");
    CHECK_EQUAL(0, num->num_of_child);
}

TEST(parse_number, PlainDecimal)
{
    struct ast_node *num;
    num = parse_number("3");
    CHECK_EQUAL(3, num->value);

    num = parse_number("10");
    CHECK_EQUAL(10, num->value);

    num = parse_number("2147483647");
    CHECK_EQUAL(2147483647, num->value);
}

TEST(parse_number, PlainOctal)
{
    struct ast_node *num;
    num = parse_number("0");
    CHECK_EQUAL(0, num->value);

    num = parse_number("077");
    CHECK_EQUAL(63, num->value);

    num = parse_number("017777777777");
    CHECK_EQUAL(2147483647, num->value);
}

TEST(parse_number, PlainHexdecimal)
{
    struct ast_node *num;
    num = parse_number("0x4");
    CHECK_EQUAL(4, num->value);

    num = parse_number("0x7FFFFFFF");
    CHECK_EQUAL(2147483647, num->value);
}

TEST(parse_number, PositiveDecimal)
{
    struct ast_node *num;
    num = parse_number("+3");
    CHECK_EQUAL(3, num->value);

    num = parse_number("+10");
    CHECK_EQUAL(10, num->value);

    num = parse_number("+2147483647");
    CHECK_EQUAL(2147483647, num->value);
}

TEST(parse_number, PositiveOctal)
{
    struct ast_node *num;
    num = parse_number("+0");
    CHECK_EQUAL(0, num->value);

    num = parse_number("+077");
    CHECK_EQUAL(63, num->value);

    num = parse_number("+017777777777");
    CHECK_EQUAL(2147483647, num->value);
}

TEST(parse_number, PositiveHexdecimal)
{
    struct ast_node *num;
    num = parse_number("+0x4");
    CHECK_EQUAL(4, num->value);

    num = parse_number("+0x7FFFFFFF");
    CHECK_EQUAL(2147483647, num->value);
}

TEST(parse_number, NegativeDecimal)
{
    struct ast_node *num;
    num = parse_number("-3");
    CHECK_EQUAL(-3, num->value);

    num = parse_number("-10");
    CHECK_EQUAL(-10, num->value);

    num = parse_number("-2147483648");
    CHECK_EQUAL(-2147483648, num->value);
}

TEST(parse_number, NegativeOctal)
{
    struct ast_node *num;
    num = parse_number("-0");
    CHECK_EQUAL(0, num->value);

    num = parse_number("-077");
    CHECK_EQUAL(-077, num->value);

    num = parse_number("-020000000000");
    CHECK_EQUAL(-2147483648, num->value);
}

TEST(parse_number, NegativeHexdecimal)
{
    struct ast_node *num;
    num = parse_number("-0x4");
    CHECK_EQUAL(-4, num->value);
    free(num);

    num = parse_number("-0x80000000");
    CHECK_EQUAL(-2147483648, num->value);
    free(num);
}

TEST(parse_number, ComplexSign)
{
    struct ast_node *num;
    num = parse_number("-+5");
    CHECK_EQUAL(-5, num->value);

    num = parse_number("-+-5");
    CHECK_EQUAL(5, num->value);

    num = parse_number("+-5");
    CHECK_EQUAL(-5, num->value);

    num = parse_number("+-+5");
    CHECK_EQUAL(-5, num->value);
}
