#include <CppUTest/TestHarness.h>

#include <sstream>

#include "kobject/KObject.h"
#include "Binding.h"

#include "kfunc/FuncPrint.h"

#include "ast/AstNode.h"

#include "parser/Parse.h"

TEST_GROUP(kfunc_FuncPrint)
{
    AstNode *node;
    KObject *res;

	Parse p;
    SyntaxErrorHandler seh;
	Binding binding;
    Binding *b;

    std::ostringstream os;

    FuncPrint *kPrint;

	void setup()
	{
        kPrint = new FuncPrint(os);
        b = &binding;
        binding.set_local(std::string("print"), kPrint);
	}

	void teardown()
	{
        delete kPrint;
		delete res;
        delete node;
	}
};

TEST(kfunc_FuncPrint, 1Arg)
{
    std::string input("print(1)");
    seh.line = &input;
    p.syntaxErrorHandler = &seh;
    node = p.parse(input.begin());
    res = node->evaluate(b);
    CHECK_EQUAL(std::string("1"), os.str());
}

TEST(kfunc_FuncPrint, 2Args)
{
    std::string input("print(1,2)");
    seh.line = &input;
    p.syntaxErrorHandler = &seh;
    node = p.parse(input.begin());
    res = node->evaluate(b);
    CHECK_EQUAL(std::string("12"), os.str());
}
