#include <cfloat>
#include <iostream>

#include <CppUTest/TestHarness.h>

#include "parser.h"

#include "kfunc/FuncC.h"

using std::string;

TEST_GROUP(AstMultiplication)
{
};

TEST(AstMultiplication, IntInt)
{
	Binding b;
    Parse p;
    AstNode *expr = p.parse("2*3");

    KInteger *res = dynamic_cast<KInteger *>(expr->evaluate(&b));
    CHECK(res);
    CHECK_EQUAL(6, res->to_i());
    delete res;
    
    delete expr;
}

TEST(AstMultiplication, IntFloat)
{
	Binding b;
    Parse p;
    AstNode *expr = p.parse("2*3.0");

    KFloat *res = dynamic_cast<KFloat *>(expr->evaluate(&b));
    CHECK(res);
    DOUBLES_EQUAL(6.0, res->to_f(), DBL_EPSILON);
    delete res;
    
    delete expr;
}

TEST(AstMultiplication, IntVector)
{
    Binding b;
    FuncC kC;
    b.set_local("c", &kC);

    Parse p;
    AstNode *expr = p.parse("2*c(3,4)");

    KVector *res = dynamic_cast<KVector *>(expr->evaluate(&b));
    CHECK(res);
    DOUBLES_EQUAL(6.0, res->vect[0], DBL_EPSILON);
    DOUBLES_EQUAL(8.0, res->vect[1], DBL_EPSILON);
    delete res;
    
    delete expr;
}

TEST(AstMultiplication, FloatInt)
{
	Binding b;
    Parse p;
    AstNode *expr = p.parse("2.0*3");

    KFloat *res = dynamic_cast<KFloat *>(expr->evaluate(&b));
    CHECK(res);
    DOUBLES_EQUAL(6.0, res->to_f(), DBL_EPSILON);
    delete res;
    
    delete expr;
}

TEST(AstMultiplication, FloatFloat)
{
	Binding b;
    Parse p;
    AstNode *expr = p.parse("2.0*3.0");

    KFloat *res = dynamic_cast<KFloat *>(expr->evaluate(&b));
    CHECK(res);
    DOUBLES_EQUAL(6.0, res->to_f(), DBL_EPSILON);
    delete res;
    
    delete expr;
}

TEST(AstMultiplication, FloatVector)
{
    Binding b;
    FuncC kC;
    b.set_local("c", &kC);

    Parse p;
    AstNode *expr = p.parse("2.0*c(3,4)");

    KVector *res = dynamic_cast<KVector *>(expr->evaluate(&b));
    CHECK(res);
    DOUBLES_EQUAL(6.0, res->vect[0], DBL_EPSILON);
    DOUBLES_EQUAL(8.0, res->vect[1], DBL_EPSILON);
    delete res;
    
    delete expr;
}

TEST(AstMultiplication, VectorInt)
{
    Binding b;
    FuncC kC;
    b.set_local("c", &kC);

    Parse p;
    AstNode *expr = p.parse("c(3,4)*2");

    KVector *res = dynamic_cast<KVector *>(expr->evaluate(&b));
    CHECK(res);
    DOUBLES_EQUAL(6.0, res->vect[0], DBL_EPSILON);
    DOUBLES_EQUAL(8.0, res->vect[1], DBL_EPSILON);
    delete res;
    
    delete expr;
}

TEST(AstMultiplication, VectorFloat)
{
    Binding b;
    FuncC kC;
    b.set_local("c", &kC);

    Parse p;
    AstNode *expr = p.parse("c(3,4)*2.0");

    KVector *res = dynamic_cast<KVector *>(expr->evaluate(&b));
    CHECK(res);
    DOUBLES_EQUAL(6.0, res->vect[0], DBL_EPSILON);
    DOUBLES_EQUAL(8.0, res->vect[1], DBL_EPSILON);
    delete res;
    
    delete expr;
}

TEST(AstMultiplication, VectorVector)
{
    Binding b;
    FuncC kC;
    b.set_local("c", &kC);

    Parse p;
    AstNode *expr = p.parse("c(3,4)*c(5,6)");

    KVector *res = dynamic_cast<KVector *>(expr->evaluate(&b));
    CHECK(res);
    DOUBLES_EQUAL(15.0, res->vect[0], DBL_EPSILON);
    DOUBLES_EQUAL(24.0, res->vect[1], DBL_EPSILON);
    delete res;
    
    delete expr;
}

