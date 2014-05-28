#include <cfloat>
#include <iostream>

#include <CppUTest/TestHarness.h>

#include "parser.h"

using std::string;

TEST_GROUP(AstReminder)
{
};

TEST(AstReminder, IntInt)
{
	Binding b;
    Parse p;
    AstNode *expr = p.parse("7%2");

    KInteger *res = dynamic_cast<KInteger *>(expr->evaluate(&b));
    CHECK(res);
    CHECK_EQUAL(1, res->to_i());
    delete res;
    
    delete expr;
}

TEST(AstReminder, IntFloat)
{
	Binding b;
    Parse p;
    AstNode *expr = p.parse("7%2.0");

    KInteger *res = dynamic_cast<KInteger *>(expr->evaluate(&b));
    CHECK(res);
    CHECK_EQUAL(1, res->to_i());
    delete res;
    
    delete expr;
}

TEST(AstReminder, FloatInt)
{
	Binding b;
    Parse p;
    AstNode *expr = p.parse("7.0%2");

    KInteger *res = dynamic_cast<KInteger *>(expr->evaluate(&b));
    CHECK(res);
    CHECK_EQUAL(1, res->to_i());
    delete res;
    
    delete expr;
}

TEST(AstReminder, FloatFloat)
{
	Binding b;
    Parse p;
    AstNode *expr = p.parse("7.0%2.0");

    KInteger *res = dynamic_cast<KInteger *>(expr->evaluate(&b));
    CHECK(res);
    CHECK_EQUAL(1, res->to_i());
    delete res;
    
    delete expr;
}
