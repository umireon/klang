#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

#include <string>

#include "ast/AstNode.h"
#include "ast/AstIf.h"

#include "parser/BaseParse.h"
#include "parser/ParseIf.h"

TEST_GROUP(ParseIf)
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
    
    class ParseCompoundMock : public BaseParse
    {
        virtual AstNode *parse(pstr_t str)
        {
            mock().actualCall("parseCompound");
            AstNode *node = new AstNode();
            node->strhead = str;
            node->strtail = str + 3;
            return node;
        }
    } parseCompoundMock;

    ParseIf parseIf, *p;
    
    AstIf *astIf;
    
    void setup()
    {
        p = &parseIf;
        p->parseExpression = &parseExpressionMock;
        p->parseCompound = &parseCompoundMock;
    }
    
    void teardown()
    {
        delete astIf;
        mock().clear();
    }
};

TEST(ParseIf, get_string)
{
    std::string input("1 3");
    mock().expectNCalls(2, "parseExpression");
    astIf = p->parse_if(input.begin());
    
    CHECK_EQUAL(input, astIf->get_string());
}

TEST(ParseIf, IfExpr)
{
    std::string input("1 3");
    mock().expectNCalls(2, "parseExpression");
    astIf = p->parse_if(input.begin());
    
    CHECK_EQUAL(std::string("1"), astIf->cond.at(0)->get_string());
    CHECK_EQUAL(std::string("3"), astIf->body.at(0)->get_string());
}

TEST(ParseIf, IfCompound)
{
    std::string input("1 {3}");
    mock().expectNCalls(1, "parseExpression");
    mock().expectNCalls(1, "parseCompound");
    astIf = p->parse_if(input.begin());
    
    CHECK_EQUAL(std::string("1"), astIf->cond.at(0)->get_string());
    CHECK_EQUAL(std::string("{3}"), astIf->body.at(0)->get_string());
}

TEST(ParseIf, ElseCompound)
{
    std::string input("1 3 else {4}");
    mock().expectNCalls(2, "parseExpression");
    mock().expectNCalls(1, "parseCompound");
    astIf = p->parse_if(input.begin());
    
    CHECK_EQUAL(std::string("1"), astIf->cond.at(0)->get_string());
    CHECK_EQUAL(std::string("3"), astIf->body.at(0)->get_string());

    CHECK_EQUAL(std::string("{4}"), astIf->body.at(1)->get_string());
}

TEST(ParseIf, IfElsif)
{
    std::string input("1 3 elsif 2 4");
    mock().expectNCalls(4, "parseExpression");
    astIf = p->parse_if(input.begin());
    
    CHECK_EQUAL(std::string("1"), astIf->cond.at(0)->get_string());
    CHECK_EQUAL(std::string("3"), astIf->body.at(0)->get_string());
    
    CHECK_EQUAL(std::string("2"), astIf->cond.at(1)->get_string());
    CHECK_EQUAL(std::string("4"), astIf->body.at(1)->get_string());
}

TEST(ParseIf, IfElse)
{
    std::string input("1 3 else 4");
    mock().expectNCalls(3, "parseExpression");
    astIf = p->parse_if(input.begin());
    
    CHECK_EQUAL(std::string("1"), astIf->cond.at(0)->get_string());
    CHECK_EQUAL(std::string("3"), astIf->body.at(0)->get_string());
    
    CHECK_EQUAL(std::string("4"), astIf->body.at(1)->get_string());
}

TEST(ParseIf, IfElsifElse)
{
    std::string input("1 3 elsif 2 4 else 6");
    mock().expectNCalls(5, "parseExpression");
    astIf = p->parse_if(input.begin());
    
    CHECK_EQUAL(std::string("1"), astIf->cond.at(0)->get_string());
    CHECK_EQUAL(std::string("3"), astIf->body.at(0)->get_string());
    
    CHECK_EQUAL(std::string("2"), astIf->cond.at(1)->get_string());
    CHECK_EQUAL(std::string("4"), astIf->body.at(1)->get_string());
    
    CHECK_EQUAL(std::string("6"), astIf->body.at(2)->get_string());
}
