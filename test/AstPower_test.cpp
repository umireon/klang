#include <cfloat>
#include <iostream>

#include <CppUTest/TestHarness.h>

#include "parser.h"

#include "kfunc/FuncC.h"

using std::string;

TEST_GROUP(AstPower)
{
};

TEST(AstPower, IntInt)
{
	Binding b;
    Parse p;
    AstNode *expr = p.parse("2**3");

    KInteger *res = dynamic_cast<KInteger *>(expr->evaluate(&b));
    CHECK(res);
    CHECK_EQUAL(8, res->to_i());
    delete res;
    
    delete expr;
}

TEST(AstPower, IntFloat)
{
	Binding b;
    Parse p;
    AstNode *expr = p.parse("2**3.0");

    KFloat *res = dynamic_cast<KFloat *>(expr->evaluate(&b));
    CHECK(res);
    DOUBLES_EQUAL(8.0, res->to_f(), DBL_EPSILON);
    delete res;
    
    delete expr;
}

TEST(AstPower, IntVector)
{
    Binding b;
    FuncC kC;
    b.set_local("c", &kC);

    Parse p;
    AstNode *expr = p.parse("2**c(3,4)");

    KVector *res = dynamic_cast<KVector *>(expr->evaluate(&b));
    CHECK(res);
    DOUBLES_EQUAL(8.0, res->vect[0], DBL_EPSILON);
    DOUBLES_EQUAL(16.0, res->vect[1], DBL_EPSILON);
    delete res;
    
    delete expr;
}

TEST(AstPower, FloatInt)
{
	Binding b;
    Parse p;
    AstNode *expr = p.parse("2.0**3");

    KFloat *res = dynamic_cast<KFloat *>(expr->evaluate(&b));
    CHECK(res);
    DOUBLES_EQUAL(8.0, res->to_f(), DBL_EPSILON);
    delete res;
    
    delete expr;
}

TEST(AstPower, FloatFloat)
{
	Binding b;
    Parse p;
    AstNode *expr = p.parse("2.0**3.0");

    KFloat *res = dynamic_cast<KFloat *>(expr->evaluate(&b));
    CHECK(res);
    DOUBLES_EQUAL(8.0, res->to_f(), DBL_EPSILON);
    delete res;
    
    delete expr;
}

TEST(AstPower, FloatVector)
{
    Binding b;
    FuncC kC;
    b.set_local("c", &kC);

    Parse p;
    AstNode *expr = p.parse("2.0**c(3,4)");

    KVector *res = dynamic_cast<KVector *>(expr->evaluate(&b));
    CHECK(res);
    DOUBLES_EQUAL(8.0, res->vect[0], DBL_EPSILON);
    DOUBLES_EQUAL(16.0, res->vect[1], DBL_EPSILON);
    delete res;
    
    delete expr;
}

TEST(AstPower, VectorInt)
{
    Binding b;
    FuncC kC;
    b.set_local("c", &kC);

    Parse p;
    AstNode *expr = p.parse("c(3,4)**2");

    KVector *res = dynamic_cast<KVector *>(expr->evaluate(&b));
    CHECK(res);
    DOUBLES_EQUAL(9.0, res->vect[0], DBL_EPSILON);
    DOUBLES_EQUAL(16.0, res->vect[1], DBL_EPSILON);
    delete res;
    
    delete expr;
}

TEST(AstPower, VectorFloat)
{
    Binding b;
    FuncC kC;
    b.set_local("c", &kC);

    Parse p;
    AstNode *expr = p.parse("c(3,4)**2.0");

    KVector *res = dynamic_cast<KVector *>(expr->evaluate(&b));
    CHECK(res);
    DOUBLES_EQUAL(9.0, res->vect[0], DBL_EPSILON);
    DOUBLES_EQUAL(16.0, res->vect[1], DBL_EPSILON);
    delete res;
    
    delete expr;
}

TEST(AstPower, VectorVector)
{
    Binding b;
    FuncC kC;
    b.set_local("c", &kC);

    Parse p;
    AstNode *expr = p.parse("c(3,4)**c(5,6)");

    KVector *res = dynamic_cast<KVector *>(expr->evaluate(&b));
    CHECK(res);
    DOUBLES_EQUAL(243.0, res->vect[0], DBL_EPSILON);
    DOUBLES_EQUAL(4096.0, res->vect[1], DBL_EPSILON);
    delete res;
    
    delete expr;
}
