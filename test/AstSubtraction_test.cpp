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

TEST_GROUP(AstSubtraction)
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

TEST(AstSubtraction, IntInt)
{
    std::string input("2-3");
    seh.line = &input;
    p.syntaxErrorHandler = &seh;
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KInteger *kint = dynamic_cast<KInteger *>(res);
    CHECK(kint);
    CHECK_EQUAL(-1, kint->to_i());
}

TEST(AstSubtraction, IntFloat)
{
    std::string input("2-3.0");
    seh.line = &input;
    p.syntaxErrorHandler = &seh;
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KFloat *kflt = dynamic_cast<KFloat *>(res);
    CHECK(kflt);
    DOUBLES_EQUAL(-1.0, kflt->to_f(), DBL_EPSILON);
}

TEST(AstSubtraction, IntVector)
{
    FuncC kC;
    b->set_local("c", &kC);
    
    std::string input("2-c(3,4)");
    seh.line = &input;
    p.syntaxErrorHandler = &seh;
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KVector *kvect = dynamic_cast<KVector *>(res);
    CHECK(kvect);
    DOUBLES_EQUAL(-1.0, kvect->vect[0], DBL_EPSILON);
    DOUBLES_EQUAL(-2.0, kvect->vect[1], DBL_EPSILON);
}

TEST(AstSubtraction, FloatInt)
{
    std::string input("2.0-3");
    seh.line = &input;
    p.syntaxErrorHandler = &seh;
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KFloat *kflt = dynamic_cast<KFloat *>(res);
    CHECK(kflt);
    DOUBLES_EQUAL(-1.0, kflt->to_f(), DBL_EPSILON);
}

TEST(AstSubtraction, FloatFloat)
{
    std::string input("2.0-3.0");
    seh.line = &input;
    p.syntaxErrorHandler = &seh;
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KFloat *kflt = dynamic_cast<KFloat *>(res);
    CHECK(kflt);
    DOUBLES_EQUAL(-1.0, kflt->to_f(), DBL_EPSILON);
}

TEST(AstSubtraction, FloatVector)
{
    FuncC kC;
    b->set_local("c", &kC);
    
    std::string input("2.0-c(3,4)");
    seh.line = &input;
    p.syntaxErrorHandler = &seh;
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KVector *kvect = dynamic_cast<KVector *>(res);
    CHECK(kvect);
    DOUBLES_EQUAL(-1.0, kvect->vect[0], DBL_EPSILON);
    DOUBLES_EQUAL(-2.0, kvect->vect[1], DBL_EPSILON);
}

TEST(AstSubtraction, VectorInt)
{
    FuncC kC;
    b->set_local("c", &kC);
    
    std::string input("c(3,4)-2");
    seh.line = &input;
    p.syntaxErrorHandler = &seh;
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KVector *kvect = dynamic_cast<KVector *>(res);
    CHECK(kvect);
    DOUBLES_EQUAL(1.0, kvect->vect[0], DBL_EPSILON);
    DOUBLES_EQUAL(2.0, kvect->vect[1], DBL_EPSILON);
}

TEST(AstSubtraction, VectorFloat)
{
    FuncC kC;
    b->set_local("c", &kC);
    
    std::string input("c(3,4)-2.0");
    seh.line = &input;
    p.syntaxErrorHandler = &seh;
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KVector *kvect = dynamic_cast<KVector *>(res);
    CHECK(kvect);
    DOUBLES_EQUAL(1.0, kvect->vect[0], DBL_EPSILON);
    DOUBLES_EQUAL(2.0, kvect->vect[1], DBL_EPSILON);
}

TEST(AstSubtraction, VectorVector)
{
    FuncC kC;
    b->set_local("c", &kC);
    
    std::string input("c(3,4)-c(5,6)");
    seh.line = &input;
    p.syntaxErrorHandler = &seh;
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KVector *kvect = dynamic_cast<KVector *>(res);
    CHECK(kvect);
    DOUBLES_EQUAL(-2.0, kvect->vect[0], DBL_EPSILON);
    DOUBLES_EQUAL(-2.0, kvect->vect[1], DBL_EPSILON);
}
