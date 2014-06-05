#include <CppUTest/TestHarness.h>
#include <cfloat>
#include <limits.h>

#include "parser/TokenNumber.h"

TEST_GROUP(TokenNumber)
{
    TokenNumber tokenNumber, *p;
    SyntaxErrorHandler seh;
    AstNumber *num;
    
    void setup()
    {
        p = &tokenNumber;
    }
    
    void teardown()
    {
        delete num;
    }
};

TEST(TokenNumber, get_string)
{
    std::string input("2");
    seh.line = &input;
    p->line = &input;
    p->syntaxErrorHandler = &seh;
    num = p->parse_number(input.begin());
    CHECK_EQUAL(input, num->get_string());
}

TEST(TokenNumber, NoChildren)
{
    std::string input("2");
    seh.line = &input;
    p->line = &input;
    p->syntaxErrorHandler = &seh;
    num = p->parse_number(input.begin());
    CHECK_EQUAL(0, num->size());
}

TEST(TokenNumber, PlainDecimal)
{
    std::string input("3");
    seh.line = &input;
    p->line = &input;
    p->syntaxErrorHandler = &seh;
    num = p->parse_number(input.begin());
    CHECK_EQUAL(input, num->get_string());
}

TEST(TokenNumber, Zero)
{
    std::string input("0");
    seh.line = &input;
    p->line = &input;
    p->syntaxErrorHandler = &seh;
    num = p->parse_number(input.begin());
    CHECK_EQUAL(input, num->get_string());
}

TEST(TokenNumber, PlainOctal)
{
    std::string input("077");
    seh.line = &input;
    p->line = &input;
    p->syntaxErrorHandler = &seh;
    num = p->parse_number(input.begin());
    CHECK_EQUAL(input, num->get_string());
}

TEST(TokenNumber, PlainHexdecimal)
{
    std::string input("0x4");
    seh.line = &input;
    p->line = &input;
    p->syntaxErrorHandler = &seh;
    num = p->parse_number(input.begin());
    CHECK_EQUAL(input, num->get_string());
}

TEST(TokenNumber, ZeroFloat)
{
    std::string input("0.4");
    seh.line = &input;
    p->line = &input;
    p->syntaxErrorHandler = &seh;
    num = p->parse_number(input.begin());
    CHECK_EQUAL(input, num->get_string());
}

TEST(TokenNumber, PlainFloat)
{
    std::string input("1.4");
    seh.line = &input;
    p->line = &input;
    p->syntaxErrorHandler = &seh;
    num = p->parse_number(input.begin());
    CHECK_EQUAL(input, num->get_string());
}

TEST(TokenNumber, PositiveDecimal)
{
    std::string input("+3");
    seh.line = &input;
    p->line = &input;
    p->syntaxErrorHandler = &seh;
    num = p->parse_number(input.begin());
    CHECK_EQUAL(input, num->get_string());
}

TEST(TokenNumber, PositiveZero)
{
    std::string input("+0");
    seh.line = &input;
    p->line = &input;
    p->syntaxErrorHandler = &seh;
    num = p->parse_number(input.begin());
    CHECK_EQUAL(input, num->get_string());
}

TEST(TokenNumber, PositiveOctal)
{
    std::string input("+077");
    seh.line = &input;
    p->line = &input;
    p->syntaxErrorHandler = &seh;
    num = p->parse_number(input.begin());
    CHECK_EQUAL(input, num->get_string());
}

TEST(TokenNumber, PositiveHexdecimal)
{
    std::string input("+0x4");
    seh.line = &input;
    p->line = &input;
    p->syntaxErrorHandler = &seh;
    num = p->parse_number(input.begin());
    CHECK_EQUAL(input, num->get_string());
}

TEST(TokenNumber, PositiveFloat)
{
    std::string input("+1.4");
    seh.line = &input;
    p->line = &input;
    p->syntaxErrorHandler = &seh;
    num = p->parse_number(input.begin());
    CHECK_EQUAL(input, num->get_string());
}

TEST(TokenNumber, NegativeDecimal)
{
    std::string input("-3");
    seh.line = &input;
    p->line = &input;
    p->syntaxErrorHandler = &seh;
    num = p->parse_number(input.begin());
    CHECK_EQUAL(input, num->get_string());
}

TEST(TokenNumber, NegativeZero)
{
    std::string input("-0");
    seh.line = &input;
    p->line = &input;
    p->syntaxErrorHandler = &seh;
    num = p->parse_number(input.begin());
    CHECK_EQUAL(input, num->get_string());
}

TEST(TokenNumber, NegativeOctal)
{
    std::string input("-077");
    seh.line = &input;
    p->line = &input;
    p->syntaxErrorHandler = &seh;
    num = p->parse_number(input.begin());
    CHECK_EQUAL(input, num->get_string());
}

TEST(TokenNumber, NegativeHexdecimal)
{
    std::string input("-0x4");
    seh.line = &input;
    p->line = &input;
    p->syntaxErrorHandler = &seh;
    num = p->parse_number(input.begin());
    CHECK_EQUAL(input, num->get_string());
}

TEST(TokenNumber, NegativeFloat)
{
    std::string input("-1.4");
    seh.line = &input;
    p->line = &input;
    p->syntaxErrorHandler = &seh;
    num = p->parse_number(input.begin());
    CHECK_EQUAL(input, num->get_string());
}

