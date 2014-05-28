#include <cfloat>
#include <iostream>

#include <CppUTest/TestHarness.h>

#include "parser.h"

using std::string;

TEST_GROUP(AstDivision)
{
};

TEST(AstDivision, IntInt)
{
	Binding b;
    Parse p;
    AstNode *expr = p.parse("7/2");

    KInteger *res = dynamic_cast<KInteger *>(expr->evaluate(&b));
    CHECK(res);
    CHECK_EQUAL(res->to_i(), 3);
    delete res;
    
    delete expr;
}

TEST(AstDivision, IntFloat)
{
	Binding b;
    Parse p;
    AstNode *expr = p.parse("7/2.0");

    KFloat *res = dynamic_cast<KFloat *>(expr->evaluate(&b));
    CHECK(res);
    DOUBLES_EQUAL(res->to_f(), 3.5, DBL_EPSILON);
    delete res;
    
    delete expr;
}

TEST(AstDivision, FloatInt)
{
	Binding b;
    Parse p;
    AstNode *expr = p.parse("7.0/2");

    KFloat *res = dynamic_cast<KFloat *>(expr->evaluate(&b));
    CHECK(res);
    DOUBLES_EQUAL(res->to_f(), 3.5, DBL_EPSILON);
    delete res;
    
    delete expr;
}

TEST(AstDivision, FloatFloat)
{
	Binding b;
    Parse p;
    AstNode *expr = p.parse("7.0/2.0");

    KFloat *res = dynamic_cast<KFloat *>(expr->evaluate(&b));
    CHECK(res);
    DOUBLES_EQUAL(res->to_f(), 3.5, DBL_EPSILON);
    delete res;
    
    delete expr;
}
