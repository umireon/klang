#include <CppUTest/TestHarness.h>

#include <cfloat>
#include <vector>

#include "kobject.h"
#include "kobject/KNil.h"
#include "Binding.h"

#include "kfunc/factorial.h"

#include "ast/AstNode.h"

#include "parser/Parse.h"

TEST_GROUP(kfunc_factorial)
{
    AstNode *node;
    KObject *res;

	Parse p;
	Binding binding;
    Binding *b;

    FuncFact kFact;
    FuncPerm kPerm;
    FuncComb kComb;
    FuncHmpr kHmpr;

	void setup()
	{
        b = &binding;
        binding.set_local(std::string("fact"), &kFact);
        binding.set_local(std::string("perm"), &kPerm);
        binding.set_local(std::string("comb"), &kComb);
        binding.set_local(std::string("hmpr"), &kHmpr);
	}

	void teardown()
	{
		delete node;
		delete res;
	}
};

TEST(kfunc_factorial, FactInteger)
{
    std::string input("fact(3)");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KInteger *kint = dynamic_cast<KInteger *>(res);
    CHECK(kint);
    CHECK_EQUAL(6, kint->to_i());
}

TEST(kfunc_factorial, PermInteger)
{
    std::string input("perm(4,2)");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KInteger *kint = dynamic_cast<KInteger *>(res);
    CHECK(kint);
    CHECK_EQUAL(12, kint->to_i());
}

TEST(kfunc_factorial, CombInteger)
{
    std::string input("comb(4,2)");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KInteger *kint = dynamic_cast<KInteger *>(res);
    CHECK(kint);
    CHECK_EQUAL(6, kint->to_i());
}

TEST(kfunc_factorial, HmprInteger)
{
    std::string input("hmpr(4,2)");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KInteger *kint = dynamic_cast<KInteger *>(res);
    CHECK(kint);
    CHECK_EQUAL(10, kint->to_i());
}
