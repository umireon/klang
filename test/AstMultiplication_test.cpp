#include <cfloat>
#include <iostream>

#include <CppUTest/TestHarness.h>

#include "parser.h"

using std::string;

TEST_GROUP(AstMultiplication)
{
};

TEST(AstMultiplication, IntInt)
{
	Binding b;
    Parse p;
    AstNode *expr = p.parse("2*3");

    KInteger *res = dynamic_cast<KInteger*>(expr->evaluate(&b));
    CHECK(res);
    CHECK_EQUAL(res->to_i(), 6);
    delete res;
    
    delete expr;
}

TEST(AstMultiplication, IntFloat)
{
	Binding b;
    Parse p;
    AstNode *expr = p.parse("2*3.0");

    KFloat *res = dynamic_cast<KFloat*>(expr->evaluate(&b));
    CHECK(res);
    CHECK_EQUAL(res->to_f(), 6);
    delete res;
    
    delete expr;
}

TEST(AstMultiplication, FloatInt)
{
	Binding b;
    Parse p;
    AstNode *expr = p.parse("2.0*3");

    KFloat *res = dynamic_cast<KFloat*>(expr->evaluate(&b));
    CHECK(res);
    DOUBLES_EQUAL(res->to_f(), 6.0, DBL_EPSILON);
    delete res;
    
    delete expr;
}

TEST(AstMultiplication, FloatFloat)
{
	Binding b;
    Parse p;
    AstNode *expr = p.parse("2.0*3.0");

    KFloat *res = dynamic_cast<KFloat*>(expr->evaluate(&b));
    CHECK(res);
    DOUBLES_EQUAL(res->to_f(), 6.0, DBL_EPSILON);
    delete res;
    
    delete expr;
}