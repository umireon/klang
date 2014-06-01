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

TEST_GROUP(AstPower)
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

TEST(AstPower, IntInt)
{
	std::string input("2**3");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KInteger *kint = dynamic_cast<KInteger *>(res);
    CHECK(kint);
    CHECK_EQUAL(8, kint->to_i());
}

TEST(AstPower, IntFloat)
{
	std::string input("2**3.0");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KFloat *kflt = dynamic_cast<KFloat *>(res);
    CHECK(kflt);
    DOUBLES_EQUAL(8.0, kflt->to_f(), DBL_EPSILON);
}

TEST(AstPower, IntVector)
{
    FuncC kC;
    b->set_local("c", &kC);

    std::string input("2**c(3,4)");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KVector *kvect = dynamic_cast<KVector *>(res);
    CHECK(kvect);
    DOUBLES_EQUAL(8.0, kvect->vect[0], DBL_EPSILON);
    DOUBLES_EQUAL(16.0, kvect->vect[1], DBL_EPSILON);
}

TEST(AstPower, FloatInt)
{
	std::string input("2.0**3");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KFloat *kflt = dynamic_cast<KFloat *>(res);
    CHECK(kflt);
    DOUBLES_EQUAL(8.0, kflt->to_f(), DBL_EPSILON);
}

TEST(AstPower, FloatFloat)
{
	std::string input("2.0**3.0");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KFloat *kflt = dynamic_cast<KFloat *>(res);
    CHECK(kflt);
    DOUBLES_EQUAL(8.0, kflt->to_f(), DBL_EPSILON);
}

TEST(AstPower, FloatVector)
{
    FuncC kC;
    b->set_local("c", &kC);

    std::string input("2.0**c(3,4)");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KVector *kvect = dynamic_cast<KVector *>(res);
    CHECK(kvect);
    DOUBLES_EQUAL(8.0, kvect->vect[0], DBL_EPSILON);
    DOUBLES_EQUAL(16.0, kvect->vect[1], DBL_EPSILON);
}

TEST(AstPower, VectorInt)
{
    FuncC kC;
    b->set_local("c", &kC);

    std::string input("c(3,4)**2");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KVector *kvect = dynamic_cast<KVector *>(res);
    CHECK(kvect);
    DOUBLES_EQUAL(9.0, kvect->vect[0], DBL_EPSILON);
    DOUBLES_EQUAL(16.0, kvect->vect[1], DBL_EPSILON);
}

TEST(AstPower, VectorFloat)
{
    FuncC kC;
    b->set_local("c", &kC);

    std::string input("c(3,4)**2.0");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KVector *kvect = dynamic_cast<KVector *>(res);
    CHECK(kvect);
    DOUBLES_EQUAL(9.0, kvect->vect[0], DBL_EPSILON);
    DOUBLES_EQUAL(16.0, kvect->vect[1], DBL_EPSILON);
}

TEST(AstPower, VectorVector)
{
    FuncC kC;
    b->set_local("c", &kC);

    std::string input("c(3,4)**c(5,6)");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KVector *kvect = dynamic_cast<KVector *>(res);
    CHECK(kvect);
    DOUBLES_EQUAL(243.0, kvect->vect[0], DBL_EPSILON);
    DOUBLES_EQUAL(4096.0, kvect->vect[1], DBL_EPSILON);
}
