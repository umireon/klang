#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

#include <string>

#include "ast/AstNode.h"
#include "ast/AstNumber.h"
#include "ast/AstIdentifier.h"
#include "ast/AstInvocation.h"
#include "ast/AstFunction.h"
#include "ast/AstIf.h"
#include "ast/AstParen.h"

#include "parser/BaseParse.h"
#include "parser/ParsePrimary.h"

TEST_GROUP(ParsePrimary)
{
    class ParseExpressionMock : public BaseParse
    {
        virtual AstNode *parse(pstr_t str)
        {
            mock().actualCall("parseExpression");
            AstNode *node = new AstNode();
            node->strhead = str;
            node->strtail = str + 1;
            return node;
        }
    } parseExpressionMock;
    
    class ParseFunctionMock : public BaseParse
    {
        virtual AstNode *parse(pstr_t str)
        {
            mock().actualCall("parseFunction");
            AstNode *node = new AstNode();
            node->strhead = str;
            node->strtail = str + 3;
            return node;
        }
    } parseFunctionMock;
    
    class ParseIfMock : public BaseParse
    {
        virtual AstNode *parse(pstr_t str)
        {
            mock().actualCall("parseIf");
            AstNode *node = new AstNode();
            node->strhead = str;
            node->strtail = str + 3;
            return node;
        }
    } parseIfMock;
    
    class ParseParenMock : public BaseParse
    {
        virtual AstNode *parse(pstr_t str)
        {
            mock().actualCall("parseParen");
            AstNode *node = new AstNode();
            node->strhead = str;
            node->strtail = str + 3;
            return node;
        }
    } parseParenMock;

    ParsePrimary parsePrimary, *p;
    
    AstNode *node;
    
    void setup()
    {
        p = &parsePrimary;
        p->parseExpression = &parseExpressionMock;
        p->parseFunction = &parseFunctionMock;
        p->parseIf = &parseIfMock;
        p->parseParen = &parseParenMock;
    }
    
    void teardown()
    {
        delete node;
        mock().clear();
    }
};

TEST(ParsePrimary, Number)
{
    std::string input("1");
    mock().expectOneCall("parseExpression");
    node = p->parse_primary(input.begin());
    CHECK(dynamic_cast<AstNumber *>(node));
    CHECK_EQUAL(input, node->get_string());
}

TEST(ParsePrimary, Identifier)
{
    std::string input("a");
    node = p->parse_primary(input.begin());
    CHECK(dynamic_cast<AstIdentifier *>(node));
    CHECK_EQUAL(input, node->get_string());
}

TEST(ParsePrimary, Function)
{
    std::string input("function()0");
    mock().expectOneCall("parseFunction");
    node = p->parse_primary(input.begin());
}

TEST(ParsePrimary, If)
{
    std::string input("if 0 1");
    mock().expectOneCall("parseIf");
    node = p->parse_primary(input.begin());
}

TEST(ParsePrimary, Paren)
{
    std::string input("(1)");
    mock().expectOneCall("parseParen");
    node = p->parse_primary(input.begin());
}

TEST(ParsePrimary, 0ArgInvocation)
{
    std::string input("f()");
    mock().expectOneCall("parseFunction");
    node = p->parse_primary(input.begin());
    CHECK(dynamic_cast<AstInvocation *>(node));
    CHECK_EQUAL(input, node->get_string());
}
/*
TEST(ParsePrimary, 0ArgInvocationWhitespace)
{
    std::string input("f ( )");
    node = p->parse_primary(input.begin());
    CHECK(dynamic_cast<AstInvocation *>(node));
    CHECK_EQUAL(input, node->get_string());
}

TEST(ParsePrimary, 1ArgInvocation)
{
    std::string input("f(1)");
    node = p->parse_primary(input.begin());
    CHECK(dynamic_cast<AstInvocation *>(node));
    CHECK_EQUAL(input, node->get_string());
}

TEST(ParsePrimary, 1ArgInvocationWhitespace)
{
    std::string input("f ( 1 )");
    node = p->parse_primary(input.begin());
    CHECK(dynamic_cast<AstInvocation *>(node));
    CHECK_EQUAL(input, node->get_string());
}

TEST(ParsePrimary, 2ArgInvocation)
{
    std::string input("f(1,2)");
    node = p->parse_primary(input.begin());
    CHECK(dynamic_cast<AstInvocation *>(node));
    CHECK_EQUAL(input, node->get_string());
}

TEST(ParsePrimary, 2ArgInvocationWhitespace)
{
    std::string input("f  (  1  , 2 )");
    node = p->parse_primary(input.begin());
    CHECK(dynamic_cast<AstInvocation *>(node));
    CHECK_EQUAL(input, node->get_string());
}*/
