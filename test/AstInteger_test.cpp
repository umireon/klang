#include <CppUTest/TestHarness.h>

#include <cfloat>
#include <string>

#include "kobject.h"
#include "Binding.h"

#include "ast/AstInteger.h"

#include "parser/Parse.h"

TEST_GROUP(AstInteger)
{
    Binding binding;
    Binding *b;
    
    Parse p;
    AstNode *node;
    KObject *res;
    
    void setup()
    {
        b = &binding;
    }
    
    void teardown()
    {
        delete node;
        delete res;
    }
};

TEST(AstInteger, PlainDecimal)
{
    std::string input("3");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KInteger *kint = dynamic_cast<KInteger *>(res);
    CHECK(kint);
    CHECK_EQUAL(3, kint->to_i());
    DOUBLES_EQUAL(3, kint->to_f(), DBL_EPSILON);
}

TEST(AstInteger, Zero)
{
    std::string input("0");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KInteger *kint = dynamic_cast<KInteger *>(res);
    CHECK(kint);
    CHECK_EQUAL(0, kint->to_i());
    DOUBLES_EQUAL(0, kint->to_f(), DBL_EPSILON);
}

TEST(AstInteger, PlainOctal)
{
    std::string input("077");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KInteger *kint = dynamic_cast<KInteger *>(res);
    CHECK(kint);
    CHECK_EQUAL(63, kint->to_i());
    DOUBLES_EQUAL(63, kint->to_f(), DBL_EPSILON);
}

TEST(AstInteger, PlainHexdecimal)
{
    std::string input("0x4");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KInteger *kint = dynamic_cast<KInteger *>(res);
    CHECK(kint);
    CHECK_EQUAL(4, kint->to_i());
    DOUBLES_EQUAL(4, kint->to_f(), DBL_EPSILON);
}

TEST(AstInteger, PositiveDecimal)
{
    std::string input("+3");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KInteger *kint = dynamic_cast<KInteger *>(res);
    CHECK(kint);
    CHECK_EQUAL(3, kint->to_i());
    DOUBLES_EQUAL(3, kint->to_f(), DBL_EPSILON);
}

TEST(AstInteger, PositiveZero)
{
    std::string input("+0");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KInteger *kint = dynamic_cast<KInteger *>(res);
    CHECK(kint);
    CHECK_EQUAL(0, kint->to_i());
    DOUBLES_EQUAL(0, kint->to_f(), DBL_EPSILON);
}

TEST(AstInteger, PositiveOctal)
{
    std::string input("+077");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KInteger *kint = dynamic_cast<KInteger *>(res);
    CHECK(kint);
    CHECK_EQUAL(63, kint->to_i());
    DOUBLES_EQUAL(63, kint->to_f(), DBL_EPSILON);
}

TEST(AstInteger, PositiveHexdecimal)
{
    std::string input("+0x4");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KInteger *kint = dynamic_cast<KInteger *>(res);
    CHECK(kint);
    CHECK_EQUAL(4, kint->to_i());
    DOUBLES_EQUAL(4, kint->to_f(), DBL_EPSILON);
}

TEST(AstInteger, NegativeDecimal)
{
    std::string input("-3");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KInteger *kint = dynamic_cast<KInteger *>(res);
    CHECK(kint);
    CHECK_EQUAL(-3, kint->to_i());
    DOUBLES_EQUAL(-3, kint->to_f(), DBL_EPSILON);
}

TEST(AstInteger, NegativeZero)
{
    std::string input("-0");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KInteger *kint = dynamic_cast<KInteger *>(res);
    CHECK(kint);
    CHECK_EQUAL(0, kint->to_i());
    DOUBLES_EQUAL(0, kint->to_f(), DBL_EPSILON);
}

TEST(AstInteger, NegativeOctal)
{
    std::string input("-077");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KInteger *kint = dynamic_cast<KInteger *>(res);
    CHECK(kint);
    CHECK_EQUAL(-63, kint->to_i());
    DOUBLES_EQUAL(-63, kint->to_f(), DBL_EPSILON);
}

TEST(AstInteger, NegativeHexdecimal)
{
    std::string input("-0x4");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KInteger *kint = dynamic_cast<KInteger *>(res);
    CHECK(kint);
    CHECK_EQUAL(-4, kint->to_i());
    DOUBLES_EQUAL(-4, kint->to_f(), DBL_EPSILON);
}
