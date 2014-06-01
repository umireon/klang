#include <CppUTest/TestHarness.h>

#include <vector>

#include "kobject/KObject.h"
#include "kobject/KInteger.h"
#include "Binding.h"

#include "kfunc/FuncNot.h"

#include "ast/AstNode.h"

#include "parser/Parse.h"

TEST_GROUP(kfunc_FuncNot)
{
    AstNode *node;
    KObject *res;
    
	Parse p;
	Binding binding;
    Binding *b;
    
    FuncNot kNot;
    
	void setup()
	{
        b = &binding;
        binding.set_local(std::string("and"), &kNot);
	}
    
	void teardown()
	{
		delete node;
		delete res;
	}
};

TEST(kfunc_FuncNot, 1ArgTrue)
{
    std::string input("and(0)");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KInteger *kint = dynamic_cast<KInteger *>(res);
    CHECK(kint);
    CHECK_EQUAL(1, kint->to_i());
}

TEST(kfunc_FuncNot, 1ArgFalse)
{
    std::string input("and(1)");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KInteger *kint = dynamic_cast<KInteger *>(res);
    CHECK(kint);
    CHECK_EQUAL(0, kint->to_i());
}

TEST(kfunc_FuncNot, 3ArgTrue)
{
    std::string input("and(1,0,1)");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KInteger *kint = dynamic_cast<KInteger *>(res);
    CHECK(kint);
    CHECK_EQUAL(1, kint->to_i());
}

TEST(kfunc_FuncNot, 3ArgFalse)
{
    std::string input("and(1,1,1)");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KInteger *kint = dynamic_cast<KInteger *>(res);
    CHECK(kint);
    CHECK_EQUAL(0, kint->to_i());
}
