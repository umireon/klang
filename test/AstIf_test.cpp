#include <CppUTest/TestHarness.h>

#include <string>

#include "kobject/KObject.h"
#include "kobject/KInteger.h"
#include "kobject/KNil.h"
#include "Binding.h"

#include "ast/AstIf.h"
#include "ast/AstInteger.h"

#include "parser/Parse.h"

TEST_GROUP(AstIf)
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

TEST(AstIf, IfTrue)
{
    std::string input("if 1 2");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KInteger *kint = dynamic_cast<KInteger *>(res);
    CHECK(kint);
    CHECK_EQUAL(2, kint->to_i());
}

TEST(AstIf, IfFalse)
{
    std::string input("if 0 2");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KNil *knil = dynamic_cast<KNil *>(res);
    CHECK(knil);
}

TEST(AstIf, IfFalseElse)
{
    std::string input("if 0 2 else 4");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KInteger *kint = dynamic_cast<KInteger *>(res);
    CHECK(kint);
    CHECK_EQUAL(4, kint->to_i());
}

TEST(AstIf, IfTrueElsif)
{
    std::string input("if 1 2 elsif 1 4");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KInteger *kint = dynamic_cast<KInteger *>(res);
    CHECK(kint);
    CHECK_EQUAL(2, kint->to_i());
}

TEST(AstIf, IfFalseElsifTrue)
{
    std::string input("if 0 2 elsif 1 4");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KInteger *kint = dynamic_cast<KInteger *>(res);
    CHECK(kint);
    CHECK_EQUAL(4, kint->to_i());
}

TEST(AstIf, IfFalseElsifFalse)
{
    std::string input("if 0 2 elsif 0 4");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KNil *knil = dynamic_cast<KNil *>(res);
    CHECK(knil);
}

TEST(AstIf, IfFalseElsifFalseElse)
{
    std::string input("if 0 2 elsif 0 4 else 6");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KInteger *kint = dynamic_cast<KInteger *>(res);
    CHECK(kint);
    CHECK_EQUAL(6, kint->to_i());
}

TEST(AstIf, IfFalseElsifFalseElsifTrue)
{
    std::string input("if 0 2 elsif 0 4 elsif 1 6");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KInteger *kint = dynamic_cast<KInteger *>(res);
    CHECK(kint);
    CHECK_EQUAL(6, kint->to_i());
}

TEST(AstIf, IfFalseElsifFalseElsifFalseElse)
{
    std::string input("if 0 2 elsif 0 4 elsif 0 6 else 8");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KInteger *kint = dynamic_cast<KInteger *>(res);
    CHECK(kint);
    CHECK_EQUAL(8, kint->to_i());
}
