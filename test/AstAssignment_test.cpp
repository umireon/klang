#include <CppUTest/TestHarness.h>

#include <string>

#include "kobject/KObject.h"
#include "kobject/KInteger.h"
#include "kobject/KFunctionAst.h"
#include "Binding.h"

#include "ast/AstInteger.h"

#include "parser/Parse.h"

TEST_GROUP(AstAssignment)
{
    Binding binding;
    Binding *b;
    
    Parse p;
    AstNode *node;
    
    void setup()
    {
        b = &binding;
    }
    
    void teardown()
    {
    }
};

TEST(AstAssignment, KInteger)
{
    std::string input("a=1");
    AstNode *node = p.parse(input.begin());
    KObject *res = node->evaluate(b);
    delete node;
    KInteger *kint = dynamic_cast<KInteger *>(res);
    CHECK(kint);
    CHECK_EQUAL(1, kint->to_i());
    delete res;
    
    KObject *sto = b->get_local(std::string("a"));
    KInteger *kint2 = dynamic_cast<KInteger *>(sto);
    CHECK(kint2);
    CHECK_EQUAL(1, kint2->to_i());
    delete sto;
}

TEST(AstAssignment, KFunctionAst)
{
    std::string input("a=function(x)x");
    node = p.parse(input.begin());
    KObject *res = node->evaluate(b);
    delete node;

    KFunctionAst *kfunc = dynamic_cast<KFunctionAst *>(res);
    CHECK(kfunc);
    delete res;
    
    KObject *sto = b->get_local(std::string("a"));
    KFunctionAst *kfunc2 = dynamic_cast<KFunctionAst *>(sto);
    CHECK(kfunc2);

    std::vector<KObject *> args;
    args.push_back(new KInteger(1));
    KObject *res2 = kfunc2->invoke(args);
    delete sto;

    KInteger *kint = dynamic_cast<KInteger *>(res2);
    CHECK(kint);
    CHECK_EQUAL(1, kint->to_i());
    delete res2;
}
