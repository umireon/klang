#include <CppUTest/TestHarness.h>
#include <cfloat>
#include <limits.h>

#include "parser.h"

TEST_GROUP(ParseNumber)
{
    Binding *b;
    void setup()
    {
        b = new Binding();
    }
    void teardown()
    {
        delete b;
    }
};

TEST(ParseNumber, Number)
{
    ParseNumber p;
    AstNumber *num = p.parse_number("2");
    CHECK(dynamic_cast<AstNumber*>(num));
    
    delete num;
}

TEST(ParseNumber, NoChildren)
{
    ParseNumber p;
    AstNumber *num;
    num = p.parse_number("2");
    CHECK_EQUAL(0, num->size());
    
    delete num;
}

TEST(ParseNumber, PlainDecimal)
{
    ParseNumber p;
    AstNumber *num;
    num = p.parse_number("3");
    KNumber *val = num->evaluate(b);
    CHECK_EQUAL(3, val->to_i());
    DOUBLES_EQUAL(3, val->to_f(), DBL_EPSILON);
    
    delete num;
    delete val;
}

TEST(ParseNumber, Zero)
{
    ParseNumber p;
    AstNumber *num = p.parse_number("0");
    KNumber *val = num->evaluate(b);
    CHECK_EQUAL(0, val->to_i());
    DOUBLES_EQUAL(0, val->to_f(), DBL_EPSILON);
    
    delete num;
    delete val;
}

TEST(ParseNumber, PlainOctal)
{
    ParseNumber p;
    AstNumber *num;
    num = p.parse_number("077");
    KNumber *val = num->evaluate(b);
    CHECK_EQUAL(63, val->to_i());
    DOUBLES_EQUAL(63, val->to_f(), DBL_EPSILON);
    
    delete num;
    delete val;
}

TEST(ParseNumber, PlainHexdecimal)
{
    ParseNumber p;
    AstNumber *num;
    num = p.parse_number("0x4");
    KNumber *val = num->evaluate(b);
    CHECK_EQUAL(4, val->to_i());
    DOUBLES_EQUAL(4, val->to_f(), DBL_EPSILON);
    
    delete num;
    delete val;
}

TEST(ParseNumber, ZeroFloat)
{
    ParseNumber p;
    AstNumber *num;
    num = p.parse_number("0.4");
    KNumber *val = num->evaluate(b);
    CHECK_EQUAL(0, val->to_i());
    DOUBLES_EQUAL(0.4, val->to_f(), DBL_EPSILON);
    
    delete num;
    delete val;
}

TEST(ParseNumber, PlainFloat)
{
    ParseNumber p;
    AstNumber *num;
    num = p.parse_number("1.4");
    KNumber *val = num->evaluate(b);
    CHECK_EQUAL(1, val->to_i());
    DOUBLES_EQUAL(1.4, val->to_f(), DBL_EPSILON);
    
    delete num;
    delete val;
}

TEST(ParseNumber, PositiveDecimal)
{
    ParseNumber p;
    AstNumber *num;
    num = p.parse_number("+3");
    KNumber *val = num->evaluate(b);
    CHECK_EQUAL(3, val->to_i());
    DOUBLES_EQUAL(3, val->to_f(), DBL_EPSILON);
    
    delete num;
    delete val;
}

TEST(ParseNumber, PositiveZero)
{
    ParseNumber p;
    AstNumber *num;
    num = p.parse_number("+0");
    KNumber *val = num->evaluate(b);
    CHECK_EQUAL(0, val->to_i());
    DOUBLES_EQUAL(0, val->to_f(), DBL_EPSILON);
    
    delete num;
    delete val;
}

TEST(ParseNumber, PositiveOctal)
{
    ParseNumber p;
    AstNumber *num;
    num = p.parse_number("+077");
    KNumber *val = num->evaluate(b);
    CHECK_EQUAL(63, val->to_i());
    DOUBLES_EQUAL(63, val->to_f(), DBL_EPSILON);
    
    delete num;
    delete val;
}

TEST(ParseNumber, PositiveHexdecimal)
{
    ParseNumber p;
    AstNumber *num;
    num = p.parse_number("+0x4");
    KNumber *val = num->evaluate(b);
    CHECK_EQUAL(4, val->to_i());
    DOUBLES_EQUAL(4, val->to_f(), DBL_EPSILON);
    
    delete num;
    delete val;
}

TEST(ParseNumber, PositiveFloat)
{
    ParseNumber p;
    AstNumber *num;
    num = p.parse_number("+1.4");
    KNumber *val = num->evaluate(b);
    CHECK_EQUAL(1, val->to_i());
    DOUBLES_EQUAL(1.4, val->to_f(), DBL_EPSILON);
    
    delete num;
    delete val;
}

TEST(ParseNumber, NegativeDecimal)
{
    ParseNumber p;
    AstNumber *num;
    num = p.parse_number("-3");
    KNumber *val = num->evaluate(b);
    CHECK_EQUAL(-3, val->to_i());
    DOUBLES_EQUAL(-3, val->to_f(), DBL_EPSILON);
    
    delete num;
    delete val;
}

TEST(ParseNumber, NegativeZero)
{
    ParseNumber p;
    AstNumber *num;
    num = p.parse_number("-0");
    KNumber *val = num->evaluate(b);
    CHECK_EQUAL(0, val->to_i());
    DOUBLES_EQUAL(0, val->to_f(), DBL_EPSILON);
    
    delete num;
    delete val;
}

TEST(ParseNumber, NegativeOctal)
{
    ParseNumber p;
    AstNumber *num;
    num = p.parse_number("-077");
    KNumber *val = num->evaluate(b);
    CHECK_EQUAL(-63, val->to_i());
    DOUBLES_EQUAL(-63, val->to_f(), DBL_EPSILON);
    
    delete num;
    delete val;
}

TEST(ParseNumber, NegativeHexdecimal)
{
    ParseNumber p;
    AstNumber *num;
    num = p.parse_number("-0x4");
    KNumber *val = num->evaluate(b);
    CHECK_EQUAL(-4, val->to_i());
    DOUBLES_EQUAL(-4, val->to_f(), DBL_EPSILON);
    
    delete num;
    delete val;
}

TEST(ParseNumber, NegativeFloat)
{
    ParseNumber p;
    AstNumber *num;
    num = p.parse_number("-1.4");
    KNumber *val = num->evaluate(b);
    CHECK_EQUAL(-1, val->to_i());
    DOUBLES_EQUAL(-1.4, val->to_f(), DBL_EPSILON);
    
    delete num;
    delete val;
}
