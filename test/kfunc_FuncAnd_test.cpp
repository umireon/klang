#include <CppUTest/TestHarness.h>

#include <vector>

#include "kobject/KObject.h"
#include "kobject/KInteger.h"
#include "Binding.h"

#include "kfunc/FuncAnd.h"

#include "ast/AstNode.h"

#include "parser/Parse.h"

TEST_GROUP(kfunc_FuncAnd)
{
    AstNode *node;
    KObject *res;
    
	Parse p;
	Binding binding;
    Binding *b;
    
    FuncAnd kAnd;
    
	void setup()
	{
        b = &binding;
        binding.set_local(std::string("and"), &kAnd);
	}
    
	void teardown()
	{
		delete node;
		delete res;
	}
};

TEST(kfunc_FuncAnd, 1ArgTrue)
{
    std::string input("and(1)");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KInteger *kint = dynamic_cast<KInteger *>(res);
    CHECK(kint);
    CHECK_EQUAL(1, kint->to_i());
}

TEST(kfunc_FuncAnd, 1ArgFalse)
{
    std::string input("and(0)");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KInteger *kint = dynamic_cast<KInteger *>(res);
    CHECK(kint);
    CHECK_EQUAL(0, kint->to_i());
}

TEST(kfunc_FuncAnd, 3ArgTrue)
{
    std::string input("and(1,1,1)");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KInteger *kint = dynamic_cast<KInteger *>(res);
    CHECK(kint);
    CHECK_EQUAL(1, kint->to_i());
}

TEST(kfunc_FuncAnd, 3ArgFalse)
{
    std::string input("and(1,0,1)");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KInteger *kint = dynamic_cast<KInteger *>(res);
    CHECK(kint);
    CHECK_EQUAL(0, kint->to_i());
}
