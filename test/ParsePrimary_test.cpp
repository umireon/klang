#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

#include <string>

#include "ast/AstNode.h"
#include "ast/AstNumber.h"
#include "ast/AstInteger.h"
#include "ast/AstIdentifier.h"
#include "ast/AstInvocation.h"
#include "ast/AstFunction.h"
#include "ast/AstIf.h"
#include "ast/AstParen.h"

#include "parser/BaseParse.h"
#include "parser/ParsePrimary.h"
#include "parser/TokenIdentifier.h"
#include "parser/TokenNumber.h"

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
    
    class TokenIdentifierMock : public TokenIdentifier
    {
        virtual AstIdentifier *parse_identifier(pstr_t str)
        {
            mock().actualCall("tokenIdentifier");
            return TokenIdentifier::parse_identifier(str);
        }
    } tokenIdentifierMock;
    
    class TokenNumberMock : public TokenNumber
    {
        virtual AstNumber *parse_number(pstr_t str)
        {
            mock().actualCall("tokenNumber");
            AstNumber *num = new AstInteger();
            num->strhead = str;
            num->strtail = str + 1;
            return num;
        }
    } tokenNumberMock;

    ParsePrimary parsePrimary, *p;
    SyntaxErrorHandler seh;
    
    AstNode *node;
    
    void setup()
    {
        p = &parsePrimary;
        p->parseExpression = &parseExpressionMock;
        p->parseFunction = &parseFunctionMock;
        p->parseIf = &parseIfMock;
        p->parseParen = &parseParenMock;
        p->tokenIdentifier = &tokenIdentifierMock;
        p->tokenNumber = &tokenNumberMock;
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
    mock().expectOneCall("tokenNumber");
    seh.line = &input;
    p->line = &input;
    p->tokenIdentifier->line = &input;
    p->syntaxErrorHandler = &seh;
    node = p->parse_primary(input.begin());
    CHECK(dynamic_cast<AstNumber *>(node));
    CHECK_EQUAL(input, node->get_string());
}

TEST(ParsePrimary, Identifier)
{
    std::string input("a");
    mock().expectOneCall("tokenIdentifier");
    seh.line = &input;
    p->line = &input;
    p->tokenIdentifier->line = &input;
    p->syntaxErrorHandler = &seh;
    node = p->parse_primary(input.begin());
    CHECK(dynamic_cast<AstIdentifier *>(node));
    CHECK_EQUAL(input, node->get_string());
}

TEST(ParsePrimary, Function)
{
    std::string input("function()0");
    mock().expectOneCall("parseFunction");
    mock().expectOneCall("tokenIdentifier");
    mock().expectOneCall("tokenNumber");
    seh.line = &input;
    p->line = &input;
    p->tokenIdentifier->line = &input;
    p->syntaxErrorHandler = &seh;
    node = p->parse_primary(input.begin());
}

TEST(ParsePrimary, If)
{
    std::string input("if 0 1");
    mock().expectOneCall("parseIf");
    mock().expectOneCall("tokenIdentifier");
    mock().expectNCalls(2, "tokenNumber");
    seh.line = &input;
    p->line = &input;
    p->tokenIdentifier->line = &input;
    p->syntaxErrorHandler = &seh;
    node = p->parse_primary(input.begin());
}

TEST(ParsePrimary, Paren)
{
    std::string input("(1)");
    mock().expectOneCall("parseParen");
    seh.line = &input;
    p->line = &input;
    p->tokenIdentifier->line = &input;
    p->syntaxErrorHandler = &seh;
    node = p->parse_primary(input.begin());
}

TEST(ParsePrimary, 0ArgInvocation)
{
    std::string input("f()");
    mock().expectOneCall("tokenIdentifier");
    seh.line = &input;
    p->line = &input;
    p->tokenIdentifier->line = &input;
    p->syntaxErrorHandler = &seh;
    node = p->parse_primary(input.begin());
    CHECK_EQUAL(input, node->get_string());
    
    AstInvocation *invoke = dynamic_cast<AstInvocation *>(node);
    CHECK(invoke);
    
    CHECK_EQUAL(std::string("f"), invoke->ident->get_name());
    
    AstArgument *astArgs = invoke->astArgs;
    CHECK_EQUAL(astArgs->size(), 0);
}

TEST(ParsePrimary, 0ArgInvocationWhitespace)
{
    std::string input("f ( )");
    mock().expectOneCall("tokenIdentifier");
    seh.line = &input;
    p->line = &input;
    p->tokenIdentifier->line = &input;
    p->syntaxErrorHandler = &seh;
    node = p->parse_primary(input.begin());
    CHECK_EQUAL(input, node->get_string());

    AstInvocation *invoke = dynamic_cast<AstInvocation *>(node);
    CHECK(invoke);
    
    CHECK_EQUAL(std::string("f"), invoke->ident->get_name());
    
    AstArgument *astArgs = invoke->astArgs;
    CHECK_EQUAL(astArgs->size(), 0);
}

TEST(ParsePrimary, 1ArgInvocation)
{
    std::string input("f(1)");
    mock().expectOneCall("tokenIdentifier");
    mock().expectOneCall("parseExpression");
    seh.line = &input;
    p->line = &input;
    p->tokenIdentifier->line = &input;
    p->syntaxErrorHandler = &seh;
    node = p->parse_primary(input.begin());
    CHECK_EQUAL(input, node->get_string());

    AstInvocation *invoke = dynamic_cast<AstInvocation *>(node);
    CHECK(invoke);
    
    CHECK_EQUAL(std::string("f"), invoke->ident->get_name());
    
    AstArgument *astArgs = invoke->astArgs;
    CHECK_EQUAL(astArgs->size(), 1);
    CHECK_EQUAL(std::string("1"), astArgs->children.at(0)->get_string());
}

TEST(ParsePrimary, 1ArgInvocationWhitespace)
{
    std::string input("f  (  1  )");
    mock().expectOneCall("tokenIdentifier");
    mock().expectOneCall("parseExpression");
    seh.line = &input;
    p->line = &input;
    p->tokenIdentifier->line = &input;
    p->syntaxErrorHandler = &seh;
    node = p->parse_primary(input.begin());
    CHECK_EQUAL(input, node->get_string());
    
    AstInvocation *invoke = dynamic_cast<AstInvocation *>(node);
    CHECK(invoke);
    
    CHECK_EQUAL(std::string("f"), invoke->ident->get_name());
    
    AstArgument *astArgs = invoke->astArgs;
    CHECK_EQUAL(astArgs->size(), 1);
    CHECK_EQUAL(std::string("1"), astArgs->children.at(0)->get_string());
}

TEST(ParsePrimary, 2ArgInvocation)
{
    std::string input("f(1,2)");
    mock().expectOneCall("tokenIdentifier");
    mock().expectNCalls(2, "parseExpression");
    seh.line = &input;
    p->line = &input;
    p->tokenIdentifier->line = &input;
    p->syntaxErrorHandler = &seh;
    node = p->parse_primary(input.begin());
    CHECK_EQUAL(input, node->get_string());
    
    AstInvocation *invoke = dynamic_cast<AstInvocation *>(node);
    CHECK(invoke);
    
    CHECK_EQUAL(std::string("f"), invoke->ident->get_name());
    
    AstArgument *astArgs = invoke->astArgs;
    CHECK_EQUAL(astArgs->size(), 2);
    CHECK_EQUAL(std::string("1"), astArgs->children.at(0)->get_string());
    CHECK_EQUAL(std::string("2"), astArgs->children.at(1)->get_string());
}

TEST(ParsePrimary, 2ArgInvocationWhitespace)
{
    std::string input("f  (  1  ,  2  )");
    mock().expectOneCall("tokenIdentifier");
    mock().expectNCalls(2, "parseExpression");
    seh.line = &input;
    p->line = &input;
    p->tokenIdentifier->line = &input;
    p->syntaxErrorHandler = &seh;
    node = p->parse_primary(input.begin());
    CHECK_EQUAL(input, node->get_string());
    
    AstInvocation *invoke = dynamic_cast<AstInvocation *>(node);
    CHECK(invoke);
    
    CHECK_EQUAL(std::string("f"), invoke->ident->get_name());
    
    AstArgument *astArgs = invoke->astArgs;
    CHECK_EQUAL(astArgs->size(), 2);
    CHECK_EQUAL(std::string("1"), astArgs->children.at(0)->get_string());
    CHECK_EQUAL(std::string("2"), astArgs->children.at(1)->get_string());
}
