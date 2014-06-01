#include <CppUTest/TestHarness.h>

#include <sstream>

#include "kobject/KObject.h"
#include "Binding.h"

#include "kfunc/FuncPuts.h"

#include "ast/AstNode.h"

#include "parser/Parse.h"

TEST_GROUP(kfunc_FuncPuts)
{
    AstNode *node;
    KObject *res;

	Parse p;
	Binding binding;
    Binding *b;

    std::ostringstream os;

    FuncPuts *kPuts;

	void setup()
	{
        kPuts = new FuncPuts(os);
        b = &binding;
        binding.set_local(std::string("puts"), kPuts);
	}

	void teardown()
	{
        delete kPuts;
		delete res;
        delete node;
	}
};

TEST(kfunc_FuncPuts, 1Arg)
{
    std::string input("puts(1)");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    CHECK_EQUAL(std::string("1\n"), os.str());
}

TEST(kfunc_FuncPuts, 2Args)
{
    std::string input("puts(1,2)");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    CHECK_EQUAL(std::string("1\n2\n"), os.str());
}
