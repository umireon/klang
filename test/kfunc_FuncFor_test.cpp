#include <CppUTest/TestHarness.h>

#include <vector>

#include "ast/AstNode.h"
#include "parser.h"
#include "kobject.h"
#include "kobject/KNil.h"

#include "kfunc/FuncC.h"
#include "kfunc/FuncFor.h"

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
/*
class FuncChecker : public KFunction {
public:
    std::vector<double> values;

    KObject* invoke(std::vector<KObject*> args) {
        KFloat *kflt = dynamic_cast<KFloat *>(args.at(0));
        values.push_back(kflt->to_f());
        return new KNil();
    }

    virtual FuncChecker *clone() const { return new FuncChecker(*this); }
};*/

TEST(kfunc_FuncFor, TwoArgs)
{
    //FuncChecker kChecker;
    //b.set_local(std::string("checker"), &kChecker);

    expr = p.parse("for(c(1,2,3),function(i)1)");
    res = expr->evaluate(b);
    CHECK(res);
}
