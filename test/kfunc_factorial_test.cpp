#include <CppUTest/TestHarness.h>

#include "ast.h"
#include "parser.h"
#include "kobject.h"

#include "kfunc/factorial.h"

TEST_GROUP(kfunc_factorial)
{
    AstNode *expr;
    KInteger *res;

	Parse p;
	Binding b;

    FuncFact kFact;
    FuncPerm kPerm;
    FuncComb kComb;
    FuncHmpr kHmpr;

	void setup()
	{
        b.set_local(std::string("fact"), &kFact);
        b.set_local(std::string("perm"), &kPerm);
        b.set_local(std::string("comb"), &kComb);
        b.set_local(std::string("hmpr"), &kHmpr);
	}

	void teardown()
	{
		delete expr;
		delete res;
	}
};

TEST(kfunc_factorial, FactInteger)
{
    expr = p.parse("fact(3)");
    res = dynamic_cast<KInteger *>(expr->evaluate(&b));
    CHECK(res);
    CHECK_EQUAL(6, res->to_i());
}

TEST(kfunc_factorial, PermInteger)
{
    expr = p.parse("perm(4,2)");
    res = dynamic_cast<KInteger *>(expr->evaluate(&b));
    CHECK(res);
    CHECK_EQUAL(12, res->to_i());
}

TEST(kfunc_factorial, CombInteger)
{
    expr = p.parse("comb(4,2)");
    res = dynamic_cast<KInteger *>(expr->evaluate(&b));
    CHECK(res);
    CHECK_EQUAL(6, res->to_i());
}

TEST(kfunc_factorial, HmprInteger)
{
    expr = p.parse("hmpr(4,2)");
    res = dynamic_cast<KInteger *>(expr->evaluate(&b));
    CHECK(res);
    CHECK_EQUAL(10, res->to_i());
}
