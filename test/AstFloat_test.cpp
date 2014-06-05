#include <CppUTest/TestHarness.h>

#include <cfloat>
#include <string>

#include "kobject/KObject.h"
#include "kobject/KFloat.h"
#include "Binding.h"

#include "ast/AstFloat.h"

#include "parser/Parse.h"

TEST_GROUP(AstFloat)
{
    Binding binding;
    Binding *b;
    
    Parse p;
    SyntaxErrorHandler seh;
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

TEST(AstFloat, ZeroFloat)
{
    std::string input("0.4");
    seh.line = &input;
    p.syntaxErrorHandler = &seh;
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KFloat *kflt = dynamic_cast<KFloat *>(res);
    CHECK(kflt);
    CHECK_EQUAL(0, kflt->to_i());
    DOUBLES_EQUAL(0.4, kflt->to_f(), DBL_EPSILON);
}

TEST(AstFloat, PlainFloat)
{
    std::string input("1.4");
    seh.line = &input;
    p.syntaxErrorHandler = &seh;
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KFloat *kflt = dynamic_cast<KFloat *>(res);
    CHECK(kflt);
    CHECK_EQUAL(1, kflt->to_i());
    DOUBLES_EQUAL(1.4, kflt->to_f(), DBL_EPSILON);
}

TEST(AstFloat, PositiveFloat)
{
    std::string input("+1.4");
    seh.line = &input;
    p.syntaxErrorHandler = &seh;
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KFloat *kflt = dynamic_cast<KFloat *>(res);
    CHECK(kflt);
    CHECK_EQUAL(1, kflt->to_i());
    DOUBLES_EQUAL(1.4, kflt->to_f(), DBL_EPSILON);
}

TEST(AstFloat, NegativeFloat)
{
    std::string input("-1.4");
    seh.line = &input;
    p.syntaxErrorHandler = &seh;
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KFloat *kflt = dynamic_cast<KFloat *>(res);
    CHECK(kflt);
    CHECK_EQUAL(-1, kflt->to_i());
    DOUBLES_EQUAL(-1.4, kflt->to_f(), DBL_EPSILON);
}
