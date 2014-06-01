#include <CppUTest/TestHarness.h>

#include <string>
#include <vector>

#include "kobject/KObject.h"
#include "kobject/KInteger.h"
#include "kobject/KFunctionAst.h"
#include "Binding.h"

#include "ast/AstNode.h"
#include "ast/AstInteger.h"

#include "parser/Parse.h"

TEST_GROUP(AstFunction)
{
    Binding binding;
    Binding *b;
    
    Parse p;
    AstNode *node;
    KObject *res;
    KObject *res2;
    
    void setup()
    {
        b = &binding;
    }
    
    void teardown()
    {
        delete node;
        delete res;
        delete res2;
    }
};

TEST(AstFunction, Constant)
{
    std::string input("function (x) 1");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KFunctionAst *kfunc = dynamic_cast<KFunctionAst *>(res);
    CHECK(kfunc);
    
    std::vector<KObject *> args;
    args.push_back(new KInteger(1));
    res2 = kfunc->invoke(args);
    KInteger *kint = dynamic_cast<KInteger *>(res2);
    CHECK(kint);
    CHECK_EQUAL(1, kint->to_i());
}

TEST(AstFunction, Invoke)
{
    std::string input("function (x) x");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KFunctionAst *kfunc = dynamic_cast<KFunctionAst *>(res);
    CHECK(kfunc);
    
    std::vector<KObject *> args;
    args.push_back(new KInteger(1));
    res2 = kfunc->invoke(args);
    KInteger *kint = dynamic_cast<KInteger *>(res2);
    CHECK(kint);
    CHECK_EQUAL(1, kint->to_i());
}

#ifndef __APPLE__
TEST(AstFunction, Invoke)
{
    std::string input("function (function) x");
    node = p.parse(input.begin());
    CHECK_THROWS(std::invalid_argument, node->evaluate(b));
}
#endif
