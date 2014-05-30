#include <cfloat>
#include <iostream>

#include <CppUTest/TestHarness.h>

#include "parser.h"
#include "kfunc/FuncC.h"

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

TEST(AstReminder, VectorInt)
{
    Binding b;
    FuncC kC;
    b.set_local("c", &kC);

    Parse p;
    AstNode *expr = p.parse("c(14,7)%2");

    KVector *res = dynamic_cast<KVector *>(expr->evaluate(&b));
    CHECK(res);
    DOUBLES_EQUAL(0.0, res->vect[0], DBL_EPSILON);
    DOUBLES_EQUAL(1.0, res->vect[1], DBL_EPSILON);
    delete res;
    
    delete expr;
}

TEST(AstReminder, VectorFloat)
{
    Binding b;
    FuncC kC;
    b.set_local("c", &kC);

    Parse p;
    AstNode *expr = p.parse("c(14,7)%2.0");

    KVector *res = dynamic_cast<KVector *>(expr->evaluate(&b));
    CHECK(res);
    DOUBLES_EQUAL(0.0, res->vect[0], DBL_EPSILON);
    DOUBLES_EQUAL(1.0, res->vect[1], DBL_EPSILON);
    delete res;
    
    delete expr;
}
