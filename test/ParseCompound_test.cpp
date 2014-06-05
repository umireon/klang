#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

#include <string>

#include "ast/AstNode.h"
#include "ast/AstCompound.h"

#include "parser/types.h"
#include "parser/BaseParse.h"
#include "parser/ParseCompound.h"

TEST_GROUP(ParseCompound)
{
    class ParseExpressionMock : public BaseParse
    {
        virtual AstNode *parse(pstr_t str)
        {
            mock().actualCall("parseExpression");
            AstNode *com = new AstNode();
            com->strhead = str;
            com->strtail = str + 1;
            return com;
        }
    } parseExpressionMock;

    ParseCompound parseCompound, *p;
    SyntaxErrorHandler seh;
    
    AstCompound *com;
    
    void setup()
    {
        p = &parseCompound;
        p->parseExpression = &parseExpressionMock;
    }
    
    void teardown()
    {
        delete com;
        mock().clear();
    }
};

TEST(ParseCompound, get_string)
{
    std::string input("{x}");
    mock().expectOneCall("parseExpression");
    seh.line = &input;
    p->line = &input;
    p->syntaxErrorHandler = &seh;
    com = p->parse_compound(input.begin());
    CHECK_EQUAL(input, com->get_string());
}

TEST(ParseCompound, InLine)
{
    std::string input("{x}");
    mock().expectOneCall("parseExpression");
    seh.line = &input;
    p->line = &input;
    p->syntaxErrorHandler = &seh;
    com = p->parse_compound(input.begin());
    
	CHECK_EQUAL(std::string("x"), com->children.at(0)->get_string());
}

TEST(ParseCompound, SingleLine)
{
    std::string input("{ \n\rx\r\n }");
    mock().expectOneCall("parseExpression");
    seh.line = &input;
    p->line = &input;
    p->syntaxErrorHandler = &seh;
    com = p->parse_compound(input.begin());
    
	CHECK_EQUAL(std::string("x"), com->children.at(0)->get_string());
}

TEST(ParseCompound, MultipleLine)
{
    std::string input("{\nx\n  y\rz\n}");
    mock().expectNCalls(3, "parseExpression");
    seh.line = &input;
    p->line = &input;
    p->syntaxErrorHandler = &seh;
    com = p->parse_compound(input.begin());
    
	CHECK_EQUAL(std::string("x"), com->children.at(0)->get_string());
	CHECK_EQUAL(std::string("y"), com->children.at(1)->get_string());
	CHECK_EQUAL(std::string("z"), com->children.at(2)->get_string());
}
