#include <CppUTest/TestHarness.h>

#include <vector>

#include "kobject/KObject.h"
#include "kobject/KInteger.h"
#include "Binding.h"

#include "kfunc/FuncOr.h"

#include "ast/AstNode.h"

#include "parser/Parse.h"

TEST_GROUP(kfunc_FuncOr)
{
    AstNode *node;
    KObject *res;
    
	Parse p;
    SyntaxErrorHandler seh;
	Binding binding;
    Binding *b;
    
    FuncOr kOr;
    
	void setup()
	{
        b = &binding;
        binding.set_local(std::string("or"), &kOr);
	}
    
	void teardown()
	{
		delete node;
		delete res;
	}
};

TEST(kfunc_FuncOr, 1ArgTrue)
{
    std::string input("or(1)");
    seh.line = &input;
    p.syntaxErrorHandler = &seh;
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KInteger *kint = dynamic_cast<KInteger *>(res);
    CHECK(kint);
    CHECK_EQUAL(1, kint->to_i());
}

TEST(kfunc_FuncOr, 1ArgFalse)
{
    std::string input("or(0)");
    seh.line = &input;
    p.syntaxErrorHandler = &seh;
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KInteger *kint = dynamic_cast<KInteger *>(res);
    CHECK(kint);
    CHECK_EQUAL(0, kint->to_i());
}

TEST(kfunc_FuncOr, 3ArgTrue)
{
    std::string input("or(0,1,0)");
    seh.line = &input;
    p.syntaxErrorHandler = &seh;
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KInteger *kint = dynamic_cast<KInteger *>(res);
    CHECK(kint);
    CHECK_EQUAL(1, kint->to_i());
}

TEST(kfunc_FuncOr, 3ArgFalse)
{
    std::string input("or(0,0,0)");
    seh.line = &input;
    p.syntaxErrorHandler = &seh;
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KInteger *kint = dynamic_cast<KInteger *>(res);
    CHECK(kint);
    CHECK_EQUAL(0, kint->to_i());
}
