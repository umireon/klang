#include <CppUTest/TestHarness.h>

#include "ast.h"
#include "parser.h"
#include "kobject.h"

#include "kfunc/triangle.h"

TEST_GROUP(kfunc_triangle)
{
    AstNode *expr;
    KFloat *res;

	Parse p;
	Binding b;

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
	    b.set_local(std::string("sin"), &kSin);
	    b.set_local(std::string("cos"), &kCos);
	    b.set_local(std::string("tan"), &kTan);

	    b.set_local(std::string("sinh"), &kSinh);
	    b.set_local(std::string("cosh"), &kCosh);
	    b.set_local(std::string("tanh"), &kTanh);

	    b.set_local(std::string("arcsin"), &kArcsin);
	    b.set_local(std::string("arccos"), &kArccos);
	    b.set_local(std::string("arctan"), &kArctan);
	}

	void teardown()
	{
		delete expr;
		delete res;
	}
};

TEST(kfunc_triangle, SinFloat)
{
    expr = p.parse("sin(1.57)");
    res = dynamic_cast<KFloat *>(expr->evaluate(&b));
    CHECK(res);
    DOUBLES_EQUAL(1.0, res->to_f(), 0.01);
}

TEST(kfunc_triangle, CosFloat)
{
    expr = p.parse("cos(0.0)");
    res = dynamic_cast<KFloat *>(expr->evaluate(&b));
    CHECK(res);
    DOUBLES_EQUAL(1.0, res->to_f(), 0.01);
}

TEST(kfunc_triangle, TanFloat)
{
    expr = p.parse("tan(0.785)");
    res = dynamic_cast<KFloat *>(expr->evaluate(&b));
    CHECK(res);
    DOUBLES_EQUAL(1.0, res->to_f(), 0.01);
}

TEST(kfunc_triangle, SinhFloat)
{
    expr = p.parse("sinh(1.0)");
    res = dynamic_cast<KFloat *>(expr->evaluate(&b));
    CHECK(res);
    DOUBLES_EQUAL(1.17, res->to_f(), 0.01);
}

TEST(kfunc_triangle, CoshFloat)
{
    expr = p.parse("cosh(1.0)");
    res = dynamic_cast<KFloat *>(expr->evaluate(&b));
    CHECK(res);
    DOUBLES_EQUAL(1.54, res->to_f(), 0.01);
}

TEST(kfunc_triangle, TanhFloat)
{
    expr = p.parse("tanh(1)");
    res = dynamic_cast<KFloat *>(expr->evaluate(&b));
    CHECK(res);
    DOUBLES_EQUAL(0.761, res->to_f(), 0.001);
}


TEST(kfunc_triangle, ArcsinFloat)
{
    expr = p.parse("arcsin(1.0)");
    res = dynamic_cast<KFloat *>(expr->evaluate(&b));
    CHECK(res);
    DOUBLES_EQUAL(1.57, res->to_f(), 0.01);
}

TEST(kfunc_triangle, ArccosFloat)
{
    expr = p.parse("arccos(0.0)");
    res = dynamic_cast<KFloat *>(expr->evaluate(&b));
    CHECK(res);
    DOUBLES_EQUAL(1.57, res->to_f(), 0.01);
}

TEST(kfunc_triangle, ArctanFloat)
{
    expr = p.parse("arctan(1.0)");
    res = dynamic_cast<KFloat *>(expr->evaluate(&b));
    CHECK(res);
    DOUBLES_EQUAL(0.785, res->to_f(), 0.01);

}
