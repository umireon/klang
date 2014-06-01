#include <CppUTest/TestHarness.h>

#include <cfloat>
#include <vector>

#include "ast/AstNode.h"
#include "parser.h"
#include "kobject.h"
#include "kobject/KNil.h"

#include "kfunc/FuncC.h"
#include "kfunc/FuncFor.h"
/*
TEST_GROUP(kfunc_FuncFor)
{
    AstNode *expr;
    KObject *res;

	Parse p;
	Binding binding;
    Binding *b;

    FuncC kC;
    FuncFor kFor;

	void setup()
	{
        b = &binding;
        binding.set_local(std::string("c"), &kC);
	    binding.set_local(std::string("for"), &kFor);
	}

	void teardown()
	{
		delete res;
        delete expr;
	}
};

TEST(kfunc_FuncFor, TwoArgs)
{
    expr = p.parse("for(c(1,2,3),function(i)i)");
    res = expr->evaluate(b);
    KFloat *kflt = dynamic_cast<KFloat *>(res);
    CHECK(kflt);
    DOUBLES_EQUAL(3.0, kflt->to_f(), DBL_EPSILON);
}

class FuncChecker : public KFunction {
public:
    std::vector<double>::iterator iter;
    
    KObject* invoke(std::vector<KObject *> args) {
        KFloat *kflt = dynamic_cast<KFloat *>(args.at(0));
        DOUBLES_EQUAL(*iter, kflt->to_f(), DBL_EPSILON);
        delete kflt;
        iter++;
        return new KNil();
    }
    
    virtual FuncChecker *clone() const { return new FuncChecker(*this); }
};

TEST(kfunc_FuncFor, Iteration)
{
    std::vector<double> expectedValues;
    expectedValues.push_back(1.0);
    expectedValues.push_back(2.0);
    expectedValues.push_back(3.0);

    FuncChecker kChecker;
    kChecker.iter = expectedValues.begin();
    binding.set_local(std::string("checker"), &kChecker);

    expr = p.parse("for(c(1,2,3),function(i)checker(i))");
    res = expr->evaluate(b);
}*/
