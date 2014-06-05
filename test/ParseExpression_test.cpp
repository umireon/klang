#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

#include <string>

#include "ast/AstNode.h"

#include "parser/ParseExpression.h"

TEST_GROUP(ParseExpression)
{
    class ParseNextMock : public BaseParse
    {
        virtual AstNode *parse(pstr_t str)
        {
            mock().actualCall("parse");
            AstNode *node = new AstNode();
            node->strhead = str;
            node->strtail = str + 1;
            return node;
        }
    } parseNextMock;

    ParseExpression parseExpression, *p;
    SyntaxErrorHandler seh;

    AstNode *node;
    
    void setup()
    {
        p = &parseExpression;
        p->parseNext = &parseNextMock;
    }
    
    void teardown()
    {
        delete node;
        mock().clear();
    }
};

TEST(ParseExpression, get_string)
{
    std::string input("0");
    mock().expectOneCall("parse");
    seh.line = &input;
    p->line = &input;
    p->syntaxErrorHandler = &seh;
    node = p->parse_expression(input.begin());
    CHECK_EQUAL(input, node->get_string());
}
