#include <CppUTest/TestHarness.h>

#include <cfloat>
#include <vector>

#include "kobject/KObject.h"
#include "kobject/KFloat.h"
#include "Binding.h"

#include "kfunc/triangle.h"
#include "kfunc/FuncC.h"

#include "ast/AstNode.h"

#include "parser/Parse.h"

TEST_GROUP(kfunc_triangle)
{
    AstNode *node;
    KObject *res;

	Parse p;
    SyntaxErrorHandler seh;
	Binding binding;
    Binding *b;

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

TEST(kfunc_triangle, SinFloat)
{
    FuncMath kSin(&sin);
    b->set_local("sin", &kSin);

    std::string input("sin(1.57)");
    seh.line = &input;
    p.syntaxErrorHandler = &seh;
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KFloat *kflt = dynamic_cast<KFloat *>(res);
    CHECK(kflt);
    DOUBLES_EQUAL(1.0, kflt->to_f(), 0.01);
}

TEST(kfunc_triangle, SinVector)
{
    FuncMath kSin(&sin);
    b->set_local("sin", &kSin);
    FuncC kC;
    b->set_local("c", &kC);

    std::string input("sin(c(1.57,0))");
    seh.line = &input;
    p.syntaxErrorHandler = &seh;
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KVector *kvect = dynamic_cast<KVector *>(res);
    CHECK(kvect);
    CHECK_EQUAL(2, kvect->vect.size());
    DOUBLES_EQUAL(1.0, kvect->vect[0], 0.01);
    DOUBLES_EQUAL(0.0, kvect->vect[1], 0.01);
}
