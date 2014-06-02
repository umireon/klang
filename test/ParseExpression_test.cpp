#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

#include <string>

#include "ast/AstNode.h"

#include "parser/ParseExpression.h"

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
};

TEST_GROUP(ParseExpression)
{
    ParseNextMock *pn;
    ParseExpression *p;
    AstNode *node;
    
    void setup()
    {
        pn = new ParseNextMock();
        p = new ParseExpression();
        p->parseNext = pn;
    }
    
    void teardown()
    {
        delete p;
        delete pn;
        delete node;
        mock().clear();
    }
};

TEST(ParseExpression, get_string)
{
    std::string input("0");
    mock().expectOneCall("parse");
    node = p->parse_expression(input.begin());
    CHECK_EQUAL(input, node->get_string());
}
