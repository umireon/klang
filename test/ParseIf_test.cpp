#include <CppUTest/TestHarness.h>

#include <string>

#include "ast/AstIf.h"

#include "parser/ParseIf.h"

TEST_GROUP(ParseIf)
{
    ParseIf p;
    AstIf *astIf;

    void teardown()
    {
        delete astIf;
    }
};

TEST(ParseIf, get_string)
{
    astIf = p.parse_if("1 3");
    CHECK_EQUAL(std::string("1 3"), astIf->get_string());
}

TEST(ParseIf, IfExpr)
{
    astIf = p.parse_if("1 3");
    CHECK_EQUAL(std::string("1"), astIf->cond.at(0)->get_string());
    CHECK_EQUAL(std::string("3"), astIf->body.at(0)->get_string());
}

TEST(ParseIf, IfCompound)
{
    astIf = p.parse_if("1 {3}");
    CHECK_EQUAL(std::string("1"), astIf->cond.at(0)->get_string());
    CHECK_EQUAL(std::string("{3}"), astIf->body.at(0)->get_string());
}

TEST(ParseIf, IfElsif)
{
    astIf = p.parse_if("1 3 elsif 2 4");
    CHECK_EQUAL(std::string("1"), astIf->cond.at(0)->get_string());
    CHECK_EQUAL(std::string("3"), astIf->body.at(0)->get_string());

    CHECK_EQUAL(std::string("2"), astIf->cond.at(1)->get_string());
    CHECK_EQUAL(std::string("4"), astIf->body.at(1)->get_string());
}

TEST(ParseIf, IfElse)
{
    astIf = p.parse_if("1 3 else 4");
    CHECK_EQUAL(std::string("1"), astIf->cond.at(0)->get_string());
    CHECK_EQUAL(std::string("3"), astIf->body.at(0)->get_string());

    CHECK_EQUAL(std::string("4"), astIf->body.at(1)->get_string());
}

TEST(ParseIf, IfElsifElse)
{
    astIf = p.parse_if("1 3 elsif 2 4 else 6");
    CHECK_EQUAL(std::string("1"), astIf->cond.at(0)->get_string());
    CHECK_EQUAL(std::string("3"), astIf->body.at(0)->get_string());

    CHECK_EQUAL(std::string("2"), astIf->cond.at(1)->get_string());
    CHECK_EQUAL(std::string("4"), astIf->body.at(1)->get_string());

    CHECK_EQUAL(std::string("6"), astIf->body.at(2)->get_string());
}
