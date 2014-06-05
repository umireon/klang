#include <CppUTest/TestHarness.h>

#include <string>

#include "ast/AstParameter.h"

#include "parser/ParseParameter.h"

TEST_GROUP(ParseParameter)
{
    TokenIdentifier tokenIdentifier;
    ParseParameter parseParameter, *p;
    SyntaxErrorHandler seh;
    AstParameter *astParam;

    void setup()
    {
        p = &parseParameter;
        p->tokenIdentifier = &tokenIdentifier;
    }

    void teardown()
    {
        delete astParam;
    }
};

TEST(ParseParameter, get_string)
{
    std::string input("()");
    seh.line = &input;
    p->line = &input;
    p->tokenIdentifier->line = &input;
    p->syntaxErrorHandler = &seh;
    astParam = p->parse_parameter(input.begin());
    CHECK_EQUAL(std::string("()"), astParam->get_string());
}

TEST(ParseParameter, Empty)
{
    std::string input("()");
    seh.line = &input;
    p->line = &input;
    p->tokenIdentifier->line = &input;
    p->syntaxErrorHandler = &seh;
    astParam = p->parse_parameter(input.begin());
    CHECK(astParam->params.empty());
}

TEST(ParseParameter, One)
{
    std::string input("(a)");
    seh.line = &input;
    p->line = &input;
    p->tokenIdentifier->line = &input;
    p->syntaxErrorHandler = &seh;
    astParam = p->parse_parameter(input.begin());
    CHECK_EQUAL(1, astParam->params.size());
    CHECK_EQUAL(std::string("a"), astParam->params[0]->get_string());
}

TEST(ParseParameter, More)
{
    std::string input("(a,b,c)");
    seh.line = &input;
    p->line = &input;
    p->tokenIdentifier->line = &input;
    p->syntaxErrorHandler = &seh;
    astParam = p->parse_parameter(input.begin());
    CHECK_EQUAL(3, astParam->params.size());
    CHECK_EQUAL(std::string("a"), astParam->params[0]->get_string());
    CHECK_EQUAL(std::string("b"), astParam->params[1]->get_string());
    CHECK_EQUAL(std::string("c"), astParam->params[2]->get_string());
}

TEST(ParseParameter, Whitespace)
{
    std::string input("(  a  , b  , c )");
    seh.line = &input;
    p->line = &input;
    p->tokenIdentifier->line = &input;
    p->syntaxErrorHandler = &seh;
    astParam = p->parse_parameter(input.begin());
    CHECK_EQUAL(3, astParam->params.size());
    CHECK_EQUAL(std::string("a"), astParam->params[0]->get_string());
    CHECK_EQUAL(std::string("b"), astParam->params[1]->get_string());
    CHECK_EQUAL(std::string("c"), astParam->params[2]->get_string());
}
