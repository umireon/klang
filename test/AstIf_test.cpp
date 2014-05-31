#include <CppUTest/TestHarness.h>

#include "kobject.h"
#include "kobject/KNil.h"

#include "ast/AstIf.h"
#include "ast/AstInteger.h"

#include "parser/ParseIf.h"

using std::string;

TEST_GROUP(AstIf)
{
    Binding binding;
    Binding *b;
    
    ParseIf p;
    AstIf *astIf;
    KObject *res;
    
    void setup()
    {
        b = &binding;
    }
    
    void teardown()
    {
        delete astIf;
        delete res;
    }
};

TEST(AstIf, IfTrue)
{
    astIf = p.parse_if("1 2");
    res = astIf->evaluate(b);
    KInteger *kint = dynamic_cast<KInteger *>(res);
    CHECK(kint);
    CHECK_EQUAL(2, kint->to_i());
}

TEST(AstIf, IfFalse)
{
    astIf = p.parse_if("0 2");
    res = astIf->evaluate(b);
    KNil *knil = dynamic_cast<KNil *>(res);
    CHECK(knil);
}

TEST(AstIf, IfFalseElse)
{
    astIf = p.parse_if("0 2 else 4");
    res = astIf->evaluate(b);
    KInteger *kint = dynamic_cast<KInteger *>(res);
    CHECK(kint);
    CHECK_EQUAL(4, kint->to_i());
}

TEST(AstIf, IfTrueElsif)
{
    astIf = p.parse_if("1 2 elsif 1 4");
    res = astIf->evaluate(b);
    KInteger *kint = dynamic_cast<KInteger *>(res);
    CHECK(kint);
    CHECK_EQUAL(2, kint->to_i());
}

TEST(AstIf, IfFalseElsifTrue)
{
    astIf = p.parse_if("0 2 elsif 1 4");
    res = astIf->evaluate(b);
    KInteger *kint = dynamic_cast<KInteger *>(res);
    CHECK(kint);
    CHECK_EQUAL(4, kint->to_i());
}

TEST(AstIf, IfFalseElsifFalse)
{
    astIf = p.parse_if("0 2 elsif 0 4");
    res = astIf->evaluate(b);
    KNil *knil = dynamic_cast<KNil *>(res);
    CHECK(knil);
}

TEST(AstIf, IfFalseElsifFalseElse)
{
    astIf = p.parse_if("0 2 elsif 0 4 else 6");
    res = astIf->evaluate(b);
    KInteger *kint = dynamic_cast<KInteger *>(res);
    CHECK(kint);
    CHECK_EQUAL(6, kint->to_i());
}

TEST(AstIf, IfFalseElsifFalseElsifTrue)
{
    astIf = p.parse_if("0 2 elsif 0 4 elsif 1 6");
    res = astIf->evaluate(b);
    KInteger *kint = dynamic_cast<KInteger *>(res);
    CHECK(kint);
    CHECK_EQUAL(6, kint->to_i());
}

TEST(AstIf, IfFalseElsifFalseElsifFalseElse)
{
    astIf = p.parse_if("0 2 elsif 0 4 elsif 0 6 else 8");
    res = astIf->evaluate(b);
    KInteger *kint = dynamic_cast<KInteger *>(res);
    CHECK(kint);
    CHECK_EQUAL(8, kint->to_i());
}
