#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

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
    std::string input("(1)");
    mock().expectOneCall("parseExpression");
    paren = p->parse_paren(input.begin());
    CHECK_EQUAL(input, paren->get_string());
}

TEST(ParseParen, SingleParen)
{
    std::string input("(a)");
    mock().expectOneCall("parseExpression");
    paren = p->parse_paren(input.begin());
    CHECK_EQUAL(std::string("a"), paren->children.at(0)->get_string());
}
