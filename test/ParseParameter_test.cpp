#include <CppUTest/TestHarness.h>

#include <string>

#include "parser/ParseParameter.h"

TEST_GROUP(ParseParameter)
{
    ParseParameter p;
    AstParameter *astParam;

    void teardown()
    {
        delete astParam;
    }
};

TEST(ParseParameter, get_string)
{
    astParam = p.parse_parameter("()");
    CHECK_EQUAL(std::string("()"), astParam->get_string());
}

TEST(ParseParameter, Empty)
{
    astParam = p.parse_parameter("()");
    CHECK(astParam->params.empty());
}

TEST(ParseParameter, One)
{
    astParam = p.parse_parameter("(a)");
    CHECK_EQUAL(1, astParam->params.size());
    CHECK_EQUAL(std::string("a"), astParam->params[0]->get_string());
}

TEST(ParseParameter, More)
{
    astParam = p.parse_parameter("(a,b,c)");
    CHECK_EQUAL(3, astParam->params.size());
    CHECK_EQUAL(std::string("a"), astParam->params[0]->get_string());
    CHECK_EQUAL(std::string("b"), astParam->params[1]->get_string());
    CHECK_EQUAL(std::string("c"), astParam->params[2]->get_string());
}
