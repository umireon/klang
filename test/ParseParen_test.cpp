#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

#include <ostream>
#include <string>

#include "ast/AstNode.h"
#include "ast/AstParen.h"

#include "parser/BaseParse.h"
#include "parser/ParseParen.h"

TEST_GROUP(ParseParen)
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

    ParseParen parseParen, *p;
    
    AstParen *paren;
    
    void setup()
    {
        p = &parseParen;
        p->parseExpression = &parseExpressionMock;
    }
    
    void teardown()
    {
        delete paren;
        mock().clear();
    }
};

TEST(ParseParen, get_string)
{
    std::ostringstream os;
    SyntaxErrorHandler seh(os);

    std::string input("(1)");
    mock().expectOneCall("parseExpression");
    seh.line = &input;
    p->line = &input;
    p->syntaxErrorHandler = &seh;
    paren = p->parse_paren(input.begin());
    CHECK_EQUAL(input, paren->get_string());
}

TEST(ParseParen, SingleParen)
{
    std::ostringstream os;
    SyntaxErrorHandler seh(os);

    std::string input("(a)");
    mock().expectOneCall("parseExpression");
    seh.line = &input;
    p->line = &input;
    p->syntaxErrorHandler = &seh;
    paren = p->parse_paren(input.begin());
    CHECK_EQUAL(std::string("a"), paren->children.at(0)->get_string());
}

TEST(ParseParen, SingleParenInvalidFirst)
{
    std::ostringstream os;
    SyntaxErrorHandler seh(os);

    std::string input(" (a)");
    mock().expectOneCall("parseExpression");
    seh.line = &input;
    p->line = &input;
    p->syntaxErrorHandler = &seh;
    paren = p->parse_paren(input.begin());
    CHECK_EQUAL(0, paren->children.size());
}

TEST(ParseParen, SingleParenInvalidLast)
{
    std::ostringstream os;
    SyntaxErrorHandler seh(os);

    std::string input("(a$)");
    mock().expectOneCall("parseExpression");
    seh.line = &input;
    p->line = &input;
    p->syntaxErrorHandler = &seh;
    paren = p->parse_paren(input.begin());
    CHECK_EQUAL(std::string("a"), paren->children.at(0)->get_string());
}
