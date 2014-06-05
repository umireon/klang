#include <CppUTest/TestHarness.h>

#include <string>

#include "kobject/KObject.h"
#include "kobject/KInteger.h"
#include "Binding.h"

#include "ast/AstNode.h"

#include "parser/Parse.h"

TEST_GROUP(AstGreaterThanEqual)
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

TEST(AstGreaterThanEqual, IntTrue)
{
    std::string input("3>=3");
    seh.line = &input;
    p.syntaxErrorHandler = &seh;
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KInteger *kint = dynamic_cast<KInteger *>(res);
    CHECK(kint);
    CHECK_EQUAL(1, kint->to_i());
}

TEST(AstGreaterThanEqual, IntFalse)
{
    std::string input("2>=3");
    seh.line = &input;
    p.syntaxErrorHandler = &seh;
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KInteger *kint = dynamic_cast<KInteger *>(res);
    CHECK(kint);
    CHECK_EQUAL(0, kint->to_i());
}

TEST(AstGreaterThanEqual, FloatTrue)
{
    std::string input("3.1>=3");
    seh.line = &input;
    p.syntaxErrorHandler = &seh;
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KInteger *kint = dynamic_cast<KInteger *>(res);
    CHECK(kint);
    CHECK_EQUAL(1, kint->to_i());
}

TEST(AstGreaterThanEqual, GreaterThanFloatFalse)
{
    std::string input("3>=3.1");
    seh.line = &input;
    p.syntaxErrorHandler = &seh;
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KInteger *kint = dynamic_cast<KInteger *>(res);
    CHECK(kint);
    CHECK_EQUAL(0, kint->to_i());
}
