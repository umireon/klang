#include <cfloat>
#include <iostream>

#include <CppUTest/TestHarness.h>

#include "parser.h"

#include "kfunc/FuncC.h"

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
    CHECK_EQUAL(3, res->to_i());
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
    DOUBLES_EQUAL(3.5, res->to_f(), DBL_EPSILON);
    delete res;
    
    delete expr;
}

TEST(AstDivision, IntVector)
{
    Binding b;
    FuncC kC;
    b.set_local("c", &kC);

    Parse p;
    AstNode *expr = p.parse("7/c(2,4)");

    KVector *res = dynamic_cast<KVector *>(expr->evaluate(&b));
    CHECK(res);
    DOUBLES_EQUAL(3.5, res->vect[0], DBL_EPSILON);
    DOUBLES_EQUAL(1.75, res->vect[1], DBL_EPSILON);
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
    DOUBLES_EQUAL(3.5, res->to_f(), DBL_EPSILON);
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
    DOUBLES_EQUAL(3.5, res->to_f(), DBL_EPSILON);
    delete res;
    
    delete expr;
}

TEST(AstDivision, FloatVector)
{
    Binding b;
    FuncC kC;
    b.set_local("c", &kC);

    Parse p;
    AstNode *expr = p.parse("7.0/c(2,4)");

    KVector *res = dynamic_cast<KVector *>(expr->evaluate(&b));
    CHECK(res);
    DOUBLES_EQUAL(3.5, res->vect[0], DBL_EPSILON);
    DOUBLES_EQUAL(1.75, res->vect[1], DBL_EPSILON);
    delete res;
    
    delete expr;
}

TEST(AstDivision, VectorInt)
{
    Binding b;
    FuncC kC;
    b.set_local("c", &kC);

    Parse p;
    AstNode *expr = p.parse("c(14,7)/2");

    KVector *res = dynamic_cast<KVector *>(expr->evaluate(&b));
    CHECK(res);
    DOUBLES_EQUAL(7.0, res->vect[0], DBL_EPSILON);
    DOUBLES_EQUAL(3.5, res->vect[1], DBL_EPSILON);
    delete res;
    
    delete expr;
}

TEST(AstDivision, VectorFloat)
{
    Binding b;
    FuncC kC;
    b.set_local("c", &kC);

    Parse p;
    AstNode *expr = p.parse("c(14,7)/2.0");

    KVector *res = dynamic_cast<KVector *>(expr->evaluate(&b));
    CHECK(res);
    DOUBLES_EQUAL(7.0, res->vect[0], DBL_EPSILON);
    DOUBLES_EQUAL(3.5, res->vect[1], DBL_EPSILON);
    delete res;
    
    delete expr;
}

TEST(AstDivision, VectorVector)
{
    Binding b;
    FuncC kC;
    b.set_local("c", &kC);

    Parse p;
    AstNode *expr = p.parse("c(14,7)/c(2,4)");

    KVector *res = dynamic_cast<KVector *>(expr->evaluate(&b));
    CHECK(res);
    DOUBLES_EQUAL(7.0, res->vect[0], DBL_EPSILON);
    DOUBLES_EQUAL(1.75, res->vect[1], DBL_EPSILON);
    delete res;
    
    delete expr;
}

