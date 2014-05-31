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
    std::string input("1 3");
    astIf = p.parse_if(input.begin());
    
    CHECK_EQUAL(input, astIf->get_string());
}

TEST(ParseIf, IfExpr)
{
    std::string input("1 3");
    astIf = p.parse_if(input.begin());
    
    CHECK_EQUAL(std::string("1"), astIf->cond.at(0)->get_string());
    CHECK_EQUAL(std::string("3"), astIf->body.at(0)->get_string());
}

TEST(ParseIf, IfCompound)
{
    std::string input("1 {3}");
    astIf = p.parse_if(input.begin());
    
    CHECK_EQUAL(std::string("1"), astIf->cond.at(0)->get_string());
    CHECK_EQUAL(std::string("{3}"), astIf->body.at(0)->get_string());
}

TEST(ParseIf, IfElsif)
{
    std::string input("1 3 elsif 2 4");
    astIf = p.parse_if(input.begin());
    
    CHECK_EQUAL(std::string("1"), astIf->cond.at(0)->get_string());
    CHECK_EQUAL(std::string("3"), astIf->body.at(0)->get_string());
    
    CHECK_EQUAL(std::string("2"), astIf->cond.at(1)->get_string());
    CHECK_EQUAL(std::string("4"), astIf->body.at(1)->get_string());
}

TEST(ParseIf, IfElse)
{
    std::string input("1 3 else 4");
    astIf = p.parse_if(input.begin());
    
    CHECK_EQUAL(std::string("1"), astIf->cond.at(0)->get_string());
    CHECK_EQUAL(std::string("3"), astIf->body.at(0)->get_string());
    
    CHECK_EQUAL(std::string("4"), astIf->body.at(1)->get_string());
}

TEST(ParseIf, IfElsifElse)
{
    std::string input("1 3 elsif 2 4 else 6");
    astIf = p.parse_if(input.begin());
    
    CHECK_EQUAL(std::string("1"), astIf->cond.at(0)->get_string());
    CHECK_EQUAL(std::string("3"), astIf->body.at(0)->get_string());
    
    CHECK_EQUAL(std::string("2"), astIf->cond.at(1)->get_string());
    CHECK_EQUAL(std::string("4"), astIf->body.at(1)->get_string());
    
    CHECK_EQUAL(std::string("6"), astIf->body.at(2)->get_string());
}
