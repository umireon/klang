#include <CppUTest/TestHarness.h>
#include <limits.h>

#include "../src/parser.h"

TEST_GROUP(parse_number)
{
};

TEST(parse_number, ReturnNumberNode)
{
    AstNode *num;
    num = parse_number("1");
    CHECK_EQUAL(AST_NUMBER, num->type);
    delete num;
}

TEST(parse_number, NoChildren)
{
    AstNode *num;
    num = parse_number("2");
    CHECK(num->children.empty());
    delete num;
}

TEST(parse_number, PlainDecimal)
{
    AstNode *num;
    num = parse_number("3");
    CHECK_EQUAL(3, num->value);
    delete num;

    num = parse_number("10");
    CHECK_EQUAL(10, num->value);
    delete num;

    num = parse_number("2147483647");
    CHECK_EQUAL(2147483647, num->value);
    delete num;
}

TEST(parse_number, PlainOctal)
{
    AstNode *num;
    num = parse_number("0");
    CHECK_EQUAL(0, num->value);
    delete num;

    num = parse_number("077");
    CHECK_EQUAL(63, num->value);
    delete num;

    num = parse_number("017777777777");
    CHECK_EQUAL(2147483647, num->value);
    delete num;
}

TEST(parse_number, PlainHexdecimal)
{
    AstNode *num;
    num = parse_number("0x4");
    CHECK_EQUAL(4, num->value);
    delete num;

    num = parse_number("0x7FFFFFFF");
    CHECK_EQUAL(2147483647, num->value);
    delete num;
}

TEST(parse_number, PositiveDecimal)
{
    AstNode *num;
    num = parse_number("+3");
    CHECK_EQUAL(3, num->value);
    delete num;

    num = parse_number("+10");
    CHECK_EQUAL(10, num->value);
    delete num;

    num = parse_number("+2147483647");
    CHECK_EQUAL(2147483647, num->value);
    delete num;
}

TEST(parse_number, PositiveOctal)
{
    AstNode *num;
    num = parse_number("+0");
    CHECK_EQUAL(0, num->value);
    delete num;

    num = parse_number("+077");
    CHECK_EQUAL(63, num->value);
    delete num;

    num = parse_number("+017777777777");
    CHECK_EQUAL(2147483647, num->value);
    delete num;
}

TEST(parse_number, PositiveHexdecimal)
{
    AstNode *num;
    num = parse_number("+0x4");
    CHECK_EQUAL(4, num->value);
    delete num;

    num = parse_number("+0x7FFFFFFF");
    CHECK_EQUAL(2147483647, num->value);
    delete num;
}

TEST(parse_number, NegativeDecimal)
{
    AstNode *num;
    num = parse_number("-3");
    CHECK_EQUAL(-3, num->value);
    delete num;

    num = parse_number("-10");
    CHECK_EQUAL(-10, num->value);
    delete num;

    num = parse_number("-2147483648");
    CHECK_EQUAL(-2147483648, num->value);
    delete num;
}

TEST(parse_number, NegativeOctal)
{
    AstNode *num;
    num = parse_number("-0");
    CHECK_EQUAL(0, num->value);
    delete num;

    num = parse_number("-077");
    CHECK_EQUAL(-077, num->value);
    delete num;

    num = parse_number("-020000000000");
    CHECK_EQUAL(-2147483648, num->value);
    delete num;
}

TEST(parse_number, NegativeHexdecimal)
{
    AstNode *num;
    num = parse_number("-0x4");
    CHECK_EQUAL(-4, num->value);
    delete num;

    num = parse_number("-0x80000000");
    CHECK_EQUAL(-2147483648, num->value);
    delete num;
}

TEST(parse_number, ComplexSign)
{
    AstNode *num;
    num = parse_number("-+5");
    CHECK_EQUAL(-5, num->value);
    delete num;

    num = parse_number("-+-5");
    CHECK_EQUAL(5, num->value);
    delete num;

    num = parse_number("+-5");
    CHECK_EQUAL(-5, num->value);
    delete num;

    num = parse_number("+-+5");
    CHECK_EQUAL(-5, num->value);
    delete num;
}
