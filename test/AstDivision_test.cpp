#include <CppUTest/TestHarness.h>

#include <cfloat>
#include <string>

#include "kobject/KObject.h"
#include "kobject/KInteger.h"
#include "kobject/KFloat.h"
#include "kobject/KVector.h"
#include "Binding.h"

#include "kfunc/FuncC.h"

#include "ast/AstNode.h"

#include "parser/Parse.h"

TEST_GROUP(AstDivision)
{
    Binding binding;
    Binding *b;

    Parse p;
    AstNode *node;
    KObject *res;
    
    void setup()
    {
        b = &binding;
    }
    
    void teardown()
    {
        delete node;
        delete res;
    }
};

TEST(AstDivision, IntInt)
{
    std::string input("7/2");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KInteger *kint = dynamic_cast<KInteger *>(res);
    CHECK(kint);
    CHECK_EQUAL(3, kint->to_i());
}

TEST(AstDivision, IntFloat)
{
    std::string input("7/2.0");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KFloat *kflt = dynamic_cast<KFloat *>(res);
    CHECK(kflt);
    DOUBLES_EQUAL(3.5, kflt->to_f(), DBL_EPSILON);
}

TEST(AstDivision, IntVector)
{
    FuncC kC;
    b->set_local("c", &kC);

    std::string input("7/c(2,4)");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KVector *kvect = dynamic_cast<KVector *>(res);
    CHECK(kvect);
    DOUBLES_EQUAL(3.5, kvect->vect[0], DBL_EPSILON);
    DOUBLES_EQUAL(1.75, kvect->vect[1], DBL_EPSILON);
}

TEST(AstDivision, FloatInt)
{
    std::string input("7.0/2");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KFloat *kflt = dynamic_cast<KFloat *>(res);
    CHECK(kflt);
    DOUBLES_EQUAL(3.5, kflt->to_f(), DBL_EPSILON);
}

TEST(AstDivision, FloatFloat)
{
    std::string input("7.0/2.0");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KFloat *kflt = dynamic_cast<KFloat *>(res);
    CHECK(kflt);
    DOUBLES_EQUAL(3.5, kflt->to_f(), DBL_EPSILON);
}

TEST(AstDivision, FloatVector)
{
    FuncC kC;
    b->set_local("c", &kC);
    
    std::string input("7.0/c(2,4)");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KVector *kvect = dynamic_cast<KVector *>(res);
    CHECK(kvect);
    DOUBLES_EQUAL(3.5, kvect->vect[0], DBL_EPSILON);
    DOUBLES_EQUAL(1.75, kvect->vect[1], DBL_EPSILON);
}

TEST(AstDivision, VectorInt)
{
    FuncC kC;
    b->set_local("c", &kC);
    
    std::string input("c(14,7)/2");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KVector *kvect = dynamic_cast<KVector *>(res);
    CHECK(kvect);
    DOUBLES_EQUAL(7.0, kvect->vect[0], DBL_EPSILON);
    DOUBLES_EQUAL(3.5, kvect->vect[1], DBL_EPSILON);
}

TEST(AstDivision, VectorFloat)
{
    FuncC kC;
    b->set_local("c", &kC);
    std::string input("c(14,7)/2.0");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KVector *kvect = dynamic_cast<KVector *>(res);
    CHECK(kvect);
    DOUBLES_EQUAL(7.0, kvect->vect[0], DBL_EPSILON);
    DOUBLES_EQUAL(3.5, kvect->vect[1], DBL_EPSILON);
}

TEST(AstDivision, VectorVector)
{
    FuncC kC;
    b->set_local("c", &kC);
    
    std::string input("c(14,7)/c(2,4)");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KVector *kvect = dynamic_cast<KVector *>(res);
    CHECK(kvect);
    DOUBLES_EQUAL(7.0, kvect->vect[0], DBL_EPSILON);
    DOUBLES_EQUAL(1.75, kvect->vect[1], DBL_EPSILON);
}
