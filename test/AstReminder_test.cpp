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

TEST_GROUP(AstReminder)
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

TEST(AstReminder, IntInt)
{
	std::string input("7%2");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KInteger *kint = dynamic_cast<KInteger *>(res);
    CHECK(kint);
    CHECK_EQUAL(1, kint->to_i());
}

TEST(AstReminder, IntFloat)
{
	std::string input("7%2.0");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KInteger *kint = dynamic_cast<KInteger *>(res);
    CHECK(kint);
    CHECK_EQUAL(1, kint->to_i());
}

TEST(AstReminder, FloatInt)
{
	std::string input("7.0%2");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KInteger *kint = dynamic_cast<KInteger *>(res);
    CHECK(kint);
    CHECK_EQUAL(1, kint->to_i());
}

TEST(AstReminder, FloatFloat)
{
	std::string input("7.0%2.0");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KInteger *kint = dynamic_cast<KInteger *>(res);
    CHECK(kint);
    CHECK_EQUAL(1, kint->to_i());
}

TEST(AstReminder, VectorInt)
{
    FuncC kC;
    b->set_local("c", &kC);

    std::string input("c(14,7)%2");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KVector *kvect = dynamic_cast<KVector *>(res);
    CHECK(kvect);
    DOUBLES_EQUAL(0.0, kvect->vect[0], DBL_EPSILON);
    DOUBLES_EQUAL(1.0, kvect->vect[1], DBL_EPSILON);
}

TEST(AstReminder, VectorFloat)
{
    FuncC kC;
    b->set_local("c", &kC);

    std::string input("c(14,7)%2.0");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KVector *kvect = dynamic_cast<KVector *>(res);
    CHECK(kvect);
    DOUBLES_EQUAL(0.0, kvect->vect[0], DBL_EPSILON);
    DOUBLES_EQUAL(1.0, kvect->vect[1], DBL_EPSILON);
}
