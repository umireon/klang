#include <CppUTest/TestHarness.h>
#include <limits.h>

#include "../src/parser.h"

TEST_GROUP(ParseNumber)
{
};

TEST_GROUP(parse_number)
{
};

TEST(ParseNumber, NoChildren)
{
    ParseNumber p;
    AstNumber *num;
    num = p.parse_number("02");
    CHECK_EQUAL(0, num->size());

    delete num;
}

TEST(ParseNumber, PlainDecimal)
{
    ParseNumber p;
    AstNumber *num;
    num = p.parse_number("3");
    CHECK_EQUAL(3, num->get_long());
    
    delete num;
}

TEST(ParseNumber, Zero)
{
    ParseNumber p;
    AstNumber *num = p.parse_number("0");
    CHECK_EQUAL(0, num->get_long());

    delete num;
}

TEST(ParseNumber, PlainOctal)
{
    ParseNumber p;
    AstNumber *num;
    num = p.parse_number("077");
    CHECK_EQUAL(63, num->get_long());

    delete num;
}

TEST(ParseNumber, PlainHexdecimal)
{
    ParseNumber p;
    AstNumber *num;
    num = p.parse_number("0x4");
    CHECK_EQUAL(4, num->get_long());

    delete num;
}

TEST(ParseNumber, PositiveDecimal)
{
    ParseNumber p;
    AstNumber *num;
    num = p.parse_number("+3");
    CHECK_EQUAL(3, num->get_long());
    
    delete num;
}

TEST(ParseNumber, PositiveZero)
{
    ParseNumber p;
    AstNumber *num;
    num = p.parse_number("+0");
    CHECK_EQUAL(0, num->get_long());
    
    delete num;
}

TEST(ParseNumber, PositiveOctal)
{
    ParseNumber p;
    AstNumber *num;
    num = p.parse_number("+077");
    CHECK_EQUAL(63, num->get_long());
    
    delete num;
}

TEST(ParseNumber, PositiveHexdecimal)
{
    ParseNumber p;
    AstNumber *num;
    num = p.parse_number("+0x4");
    CHECK_EQUAL(4, num->get_long());
    
    delete num;
}

TEST(ParseNumber, NegativeDecimal)
{
    ParseNumber p;
    AstNumber *num;
    num = p.parse_number("-3");
    CHECK_EQUAL(-3, num->get_long());
    
    delete num;
}

TEST(ParseNumber, NegativeZero)
{
    ParseNumber p;
    AstNumber *num;
    num = p.parse_number("-0");
    CHECK_EQUAL(0, num->get_long());
    
    delete num;
}

TEST(ParseNumber, NegativeOctal)
{
    ParseNumber p;
    AstNumber *num;
    num = p.parse_number("-077");
    CHECK_EQUAL(-077, num->get_long());
    
    delete num;
}

TEST(ParseNumber, NegativeHexdecimal)
{
    ParseNumber p;
    AstNumber *num;
    num = p.parse_number("-0x4");
    CHECK_EQUAL(-4, num->get_long());
    
    delete num;
}

