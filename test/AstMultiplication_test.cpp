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

TEST_GROUP(AstMultiplication)
{
    Binding binding;
    Binding *b;
    
    Parse p;
    SyntaxErrorHandler seh;
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

TEST(AstMultiplication, IntInt)
{
    std::string input("2*3");
    seh.line = &input;
    p.syntaxErrorHandler = &seh;
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KInteger *kint = dynamic_cast<KInteger *>(res);
    CHECK(kint);
    CHECK_EQUAL(6, kint->to_i());
}

TEST(AstMultiplication, IntFloat)
{
    std::string input("2*3.0");
    seh.line = &input;
    p.syntaxErrorHandler = &seh;
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KFloat *kflt = dynamic_cast<KFloat *>(res);
    CHECK(kflt);
    DOUBLES_EQUAL(6.0, kflt->to_f(), DBL_EPSILON);
}

TEST(AstMultiplication, IntVector)
{
    FuncC kC;
    b->set_local("c", &kC);
    
    std::string input("2*c(3,4)");
    seh.line = &input;
    p.syntaxErrorHandler = &seh;
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KVector *kvect = dynamic_cast<KVector *>(res);
    CHECK(kvect);
    DOUBLES_EQUAL(6.0, kvect->vect[0], DBL_EPSILON);
    DOUBLES_EQUAL(8.0, kvect->vect[1], DBL_EPSILON);
}

TEST(AstMultiplication, FloatInt)
{
    std::string input("2.0*3");
    seh.line = &input;
    p.syntaxErrorHandler = &seh;
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KFloat *kflt = dynamic_cast<KFloat *>(res);
    CHECK(kflt);
    DOUBLES_EQUAL(6.0, kflt->to_f(), DBL_EPSILON);
}

TEST(AstMultiplication, FloatFloat)
{
    std::string input("2.0*3.0");
    seh.line = &input;
    p.syntaxErrorHandler = &seh;
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KFloat *kflt = dynamic_cast<KFloat *>(res);
    CHECK(kflt);
    DOUBLES_EQUAL(6.0, kflt->to_f(), DBL_EPSILON);
}

TEST(AstMultiplication, FloatVector)
{
    FuncC kC;
    b->set_local("c", &kC);
    
    std::string input("2.0*c(3,4)");
    seh.line = &input;
    p.syntaxErrorHandler = &seh;
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KVector *kvect = dynamic_cast<KVector *>(res);
    CHECK(kvect);
    DOUBLES_EQUAL(6.0, kvect->vect[0], DBL_EPSILON);
    DOUBLES_EQUAL(8.0, kvect->vect[1], DBL_EPSILON);
}

TEST(AstMultiplication, VectorInt)
{
    FuncC kC;
    b->set_local("c", &kC);
    
    std::string input("c(3,4)*2");
    seh.line = &input;
    p.syntaxErrorHandler = &seh;
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KVector *kvect = dynamic_cast<KVector *>(res);
    CHECK(kvect);
    DOUBLES_EQUAL(6.0, kvect->vect[0], DBL_EPSILON);
    DOUBLES_EQUAL(8.0, kvect->vect[1], DBL_EPSILON);
}

TEST(AstMultiplication, VectorFloat)
{
    FuncC kC;
    b->set_local("c", &kC);
    
    std::string input("c(3,4)*2.0");
    seh.line = &input;
    p.syntaxErrorHandler = &seh;
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KVector *kvect = dynamic_cast<KVector *>(res);
    CHECK(kvect);
    DOUBLES_EQUAL(6.0, kvect->vect[0], DBL_EPSILON);
    DOUBLES_EQUAL(8.0, kvect->vect[1], DBL_EPSILON);
}

TEST(AstMultiplication, VectorVector)
{
    FuncC kC;
    b->set_local("c", &kC);
    
    std::string input("c(3,4)*c(5,6)");
    seh.line = &input;
    p.syntaxErrorHandler = &seh;
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KVector *kvect = dynamic_cast<KVector *>(res);
    CHECK(kvect);
    DOUBLES_EQUAL(15.0, kvect->vect[0], DBL_EPSILON);
    DOUBLES_EQUAL(24.0, kvect->vect[1], DBL_EPSILON);
}
