#include <cfloat>
#include <iostream>

#include <CppUTest/TestHarness.h>

#include "parser.h"

#include "kfunc/FuncC.h"

using std::string;

TEST_GROUP(AstAddition)
{
};

TEST(AstAddition, IntInt)
{
	Binding b;
    Parse p;
    AstNode *expr = p.parse("2+3");

    KInteger *res = dynamic_cast<KInteger *>(expr->evaluate(&b));
    CHECK(res);
    CHECK_EQUAL(5, res->to_i());
    delete res;
    
    delete expr;
}

TEST(AstAddition, IntFloat)
{
	Binding b;
    Parse p;
    AstNode *expr = p.parse("2+3.0");

    KFloat *res = dynamic_cast<KFloat *>(expr->evaluate(&b));
    CHECK(res);
    DOUBLES_EQUAL(5.0, res->to_f(), DBL_EPSILON);
    delete res;
    
    delete expr;
}

TEST(AstAddition, IntVector)
{
    Binding b;
    FuncC kC;
    b.set_local("c", &kC);

    Parse p;
    AstNode *expr = p.parse("2+c(3,4)");

    KVector *res = dynamic_cast<KVector *>(expr->evaluate(&b));
    CHECK(res);
    DOUBLES_EQUAL(5.0, res->vect[0], DBL_EPSILON);
    DOUBLES_EQUAL(6.0, res->vect[1], DBL_EPSILON);
    delete res;
    
    delete expr;
}

TEST(AstAddition, FloatInt)
{
	Binding b;
    Parse p;
    AstNode *expr = p.parse("2.0+3");

    KFloat *res = dynamic_cast<KFloat *>(expr->evaluate(&b));
    CHECK(res);
    DOUBLES_EQUAL(5.0, res->to_f(), DBL_EPSILON);
    delete res;
    
    delete expr;
}

TEST(AstAddition, FloatFloat)
{
	Binding b;
    Parse p;
    AstNode *expr = p.parse("2.0+3.0");

    KFloat *res = dynamic_cast<KFloat *>(expr->evaluate(&b));
    CHECK(res);
    DOUBLES_EQUAL(5.0, res->to_f(), DBL_EPSILON);
    delete res;
    
    delete expr;
}

TEST(AstAddition, FloatVector)
{
    Binding b;
    FuncC kC;
    b.set_local("c", &kC);

    Parse p;
    AstNode *expr = p.parse("2.0+c(3,4)");

    KVector *res = dynamic_cast<KVector *>(expr->evaluate(&b));
    CHECK(res);
    DOUBLES_EQUAL(5.0, res->vect[0], DBL_EPSILON);
    DOUBLES_EQUAL(6.0, res->vect[1], DBL_EPSILON);
    delete res;
    
    delete expr;
}

TEST(AstAddition, VectorInt)
{
    Binding b;
    FuncC kC;
    b.set_local("c", &kC);

    Parse p;
    AstNode *expr = p.parse("c(3,4)+2");

    KVector *res = dynamic_cast<KVector *>(expr->evaluate(&b));
    CHECK(res);
    DOUBLES_EQUAL(5.0, res->vect[0], DBL_EPSILON);
    DOUBLES_EQUAL(6.0, res->vect[1], DBL_EPSILON);
    delete res;
    
    delete expr;
}

TEST(AstAddition, VectorFloat)
{
    Binding b;
    FuncC kC;
    b.set_local("c", &kC);

    Parse p;
    AstNode *expr = p.parse("c(3,4)+2.0");

    KVector *res = dynamic_cast<KVector *>(expr->evaluate(&b));
    CHECK(res);
    DOUBLES_EQUAL(5.0, res->vect[0], DBL_EPSILON);
    DOUBLES_EQUAL(6.0, res->vect[1], DBL_EPSILON);
    delete res;
    
    delete expr;
}

TEST(AstAddition, VectorVector)
{
    Binding b;
    FuncC kC;
    b.set_local("c", &kC);

    Parse p;
    AstNode *expr = p.parse("c(3,4)+c(5,6)");

    KVector *res = dynamic_cast<KVector *>(expr->evaluate(&b));
    CHECK(res);
    DOUBLES_EQUAL(8.0, res->vect[0], DBL_EPSILON);
    DOUBLES_EQUAL(10.0, res->vect[1], DBL_EPSILON);
    delete res;
    
    delete expr;
}
