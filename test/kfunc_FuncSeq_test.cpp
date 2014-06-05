#include <CppUTest/TestHarness.h>

#include <cfloat>
#include <vector>
#include <sstream>

#include "kobject/KObject.h"
#include "kobject/KInteger.h"
#include "kobject/KNil.h"
#include "Binding.h"

#include "kfunc/FuncSeq.h"
#include "kfunc/FuncC.h"

#include "ast/AstNode.h"

#include "parser/Parse.h"

TEST_GROUP(kfunc_FuncSeq)
{
    AstNode *node;
    KObject *res;
    
	Parse p;
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

TEST(kfunc_FuncSeq, 1Arg)
{
    std::ostringstream os;
    SyntaxErrorHandler seh(os);
    FuncSeq kSeq(os);
    b->set_local(std::string("seq"), &kSeq);

    std::string input("seq(1)");
    seh.line = &input;
    p.syntaxErrorHandler = &seh;
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KNil *knil = dynamic_cast<KNil *>(res);
    CHECK(knil);
}

TEST(kfunc_FuncSeq, 2Arg)
{
    std::ostringstream os;
    SyntaxErrorHandler seh(os);
    FuncSeq kSeq(os);
    b->set_local(std::string("seq"), &kSeq);

    std::string input("seq(1,3)");
    seh.line = &input;
    p.syntaxErrorHandler = &seh;
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KVector *kvect = dynamic_cast<KVector *>(res);
    CHECK(kvect);
    UNSIGNED_LONGS_EQUAL(3, kvect->vect.size());
    DOUBLES_EQUAL(1.0, kvect->vect[0], DBL_EPSILON);
    DOUBLES_EQUAL(2.0, kvect->vect[1], DBL_EPSILON);
    DOUBLES_EQUAL(3.0, kvect->vect[2], DBL_EPSILON);
}

TEST(kfunc_FuncSeq, 2ArgVector)
{
    std::ostringstream os;
    SyntaxErrorHandler seh(os);
    FuncSeq kSeq(os);
    b->set_local(std::string("seq"), &kSeq);
    FuncC kC;
    b->set_local(std::string("c"), &kC);

    std::string input("seq(1,c(1,2))");
    seh.line = &input;
    p.syntaxErrorHandler = &seh;
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KNil *knil = dynamic_cast<KNil *>(res);
    CHECK(knil);
}


TEST(kfunc_FuncSeq, 3Arg)
{
    std::ostringstream os;
    SyntaxErrorHandler seh(os);
    FuncSeq kSeq(os);
    b->set_local(std::string("seq"), &kSeq);

    std::string input("seq(1,2,3)");
    seh.line = &input;
    p.syntaxErrorHandler = &seh;
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KNil *knil = dynamic_cast<KNil *>(res);
    CHECK(knil);
}