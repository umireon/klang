#include <CppUTest/TestHarness.h>

#include <cfloat>
#include <vector>

#include "kobject/KObject.h"
#include "kobject/KFloat.h"
#include "Binding.h"

#include "kfunc/triangle.h"

#include "ast/AstNode.h"

#include "parser/Parse.h"

TEST_GROUP(kfunc_triangle)
{
    AstNode *node;
    KObject *res;

	Parse p;
	Binding binding;
    Binding *b;

    FuncSin kSin;
    FuncCos kCos;
    FuncTan kTan;

    FuncSinh kSinh;
    FuncCosh kCosh;
    FuncTanh kTanh;

    FuncArcsin kArcsin;
    FuncArccos kArccos;
    FuncArctan kArctan;

	void setup()
	{
        b = &binding;
	    binding.set_local(std::string("sin"), &kSin);
	    binding.set_local(std::string("cos"), &kCos);
	    binding.set_local(std::string("tan"), &kTan);

	    binding.set_local(std::string("sinh"), &kSinh);
	    binding.set_local(std::string("cosh"), &kCosh);
	    binding.set_local(std::string("tanh"), &kTanh);

	    binding.set_local(std::string("arcsin"), &kArcsin);
	    binding.set_local(std::string("arccos"), &kArccos);
	    binding.set_local(std::string("arctan"), &kArctan);
	}

	void teardown()
	{
		delete node;
		delete res;
	}
};

TEST(kfunc_triangle, SinFloat)
{
    std::string input("sin(1.57)");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KFloat *kflt = dynamic_cast<KFloat *>(res);
    CHECK(kflt);
    DOUBLES_EQUAL(1.0, kflt->to_f(), 0.01);
}

TEST(kfunc_triangle, CosFloat)
{
    std::string input("cos(0.0)");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KFloat *kflt = dynamic_cast<KFloat *>(res);
    CHECK(kflt);
    DOUBLES_EQUAL(1.0, kflt->to_f(), 0.01);
}

TEST(kfunc_triangle, TanFloat)
{
    std::string input("tan(0.785)");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KFloat *kflt = dynamic_cast<KFloat *>(res);
    CHECK(kflt);
    DOUBLES_EQUAL(1.0, kflt->to_f(), 0.01);
}

TEST(kfunc_triangle, SinhFloat)
{
    std::string input("sinh(1.0)");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KFloat *kflt = dynamic_cast<KFloat *>(res);
    CHECK(kflt);
    DOUBLES_EQUAL(1.17, kflt->to_f(), 0.01);
}

TEST(kfunc_triangle, CoshFloat)
{
    std::string input("cosh(1.0)");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KFloat *kflt = dynamic_cast<KFloat *>(res);
    CHECK(kflt);
    DOUBLES_EQUAL(1.54, kflt->to_f(), 0.01);
}

TEST(kfunc_triangle, TanhFloat)
{
    std::string input("tanh(1)");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KFloat *kflt = dynamic_cast<KFloat *>(res);
    CHECK(kflt);
    DOUBLES_EQUAL(0.761, kflt->to_f(), 0.001);
}


TEST(kfunc_triangle, ArcsinFloat)
{
    std::string input("arcsin(1.0)");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KFloat *kflt = dynamic_cast<KFloat *>(res);
    CHECK(kflt);
    DOUBLES_EQUAL(1.57, kflt->to_f(), 0.01);
}

TEST(kfunc_triangle, ArccosFloat)
{
    std::string input("arccos(0.0)");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KFloat *kflt = dynamic_cast<KFloat *>(res);
    CHECK(kflt);
    DOUBLES_EQUAL(1.57, kflt->to_f(), 0.01);
}

TEST(kfunc_triangle, ArctanFloat)
{
    std::string input("arctan(1.0)");
    node = p.parse(input.begin());
    res = node->evaluate(b);
    KFloat *kflt = dynamic_cast<KFloat *>(res);
    CHECK(kflt);
    DOUBLES_EQUAL(0.785, kflt->to_f(), 0.01);

}
