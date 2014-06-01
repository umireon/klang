#include <CppUTest/TestHarness.h>

#include <string>

#include "kobject.h"
#include "kobject/KNil.h"
#include "Binding.h"

#include "ast/AstIf.h"
#include "ast/AstInteger.h"

#include "parser/ParseIf.h"

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
    std::string input("1 2");
    astIf = p.parse_if(input.begin());
    res = astIf->evaluate(b);
    KInteger *kint = dynamic_cast<KInteger *>(res);
    CHECK(kint);
    CHECK_EQUAL(2, kint->to_i());
}

TEST(AstIf, IfFalse)
{
    std::string input("0 2");
    astIf = p.parse_if(input.begin());
    res = astIf->evaluate(b);
    KNil *knil = dynamic_cast<KNil *>(res);
    CHECK(knil);
}

TEST(AstIf, IfFalseElse)
{
    std::string input("0 2 else 4");
    astIf = p.parse_if(input.begin());
    res = astIf->evaluate(b);
    KInteger *kint = dynamic_cast<KInteger *>(res);
    CHECK(kint);
    CHECK_EQUAL(4, kint->to_i());
}

TEST(AstIf, IfTrueElsif)
{
    std::string input("1 2 elsif 1 4");
    astIf = p.parse_if(input.begin());
    res = astIf->evaluate(b);
    KInteger *kint = dynamic_cast<KInteger *>(res);
    CHECK(kint);
    CHECK_EQUAL(2, kint->to_i());
}

TEST(AstIf, IfFalseElsifTrue)
{
    std::string input("0 2 elsif 1 4");
    astIf = p.parse_if(input.begin());
    res = astIf->evaluate(b);
    KInteger *kint = dynamic_cast<KInteger *>(res);
    CHECK(kint);
    CHECK_EQUAL(4, kint->to_i());
}

TEST(AstIf, IfFalseElsifFalse)
{
    std::string input("0 2 elsif 0 4");
    astIf = p.parse_if(input.begin());
    res = astIf->evaluate(b);
    KNil *knil = dynamic_cast<KNil *>(res);
    CHECK(knil);
}

TEST(AstIf, IfFalseElsifFalseElse)
{
    std::string input("0 2 elsif 0 4 else 6");
    astIf = p.parse_if(input.begin());
    res = astIf->evaluate(b);
    KInteger *kint = dynamic_cast<KInteger *>(res);
    CHECK(kint);
    CHECK_EQUAL(6, kint->to_i());
}

TEST(AstIf, IfFalseElsifFalseElsifTrue)
{
    std::string input("0 2 elsif 0 4 elsif 1 6");
    astIf = p.parse_if(input.begin());
    res = astIf->evaluate(b);
    KInteger *kint = dynamic_cast<KInteger *>(res);
    CHECK(kint);
    CHECK_EQUAL(6, kint->to_i());
}

TEST(AstIf, IfFalseElsifFalseElsifFalseElse)
{
    std::string input("0 2 elsif 0 4 elsif 0 6 else 8");
    astIf = p.parse_if(input.begin());
    res = astIf->evaluate(b);
    KInteger *kint = dynamic_cast<KInteger *>(res);
    CHECK(kint);
    CHECK_EQUAL(8, kint->to_i());
}
