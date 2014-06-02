#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

#include <string>

#include "ast/AstAddition.h"
#include "ast/AstAssignment.h"
#include "ast/AstCompound.h"
#include "ast/AstIdentifier.h"
#include "ast/AstNumber.h"

#include "parser/ParseFunction.h"

TEST_GROUP(ParseFunction)
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

    ParseFunction parseFunction, *p;
    
    AstFunction *astFunc;
    
    void setup()
    {
        p = &parseFunction;
        p->parseExpression = &parseExpressionMock;
        p->parseCompound = &parseCompoundMock;
    }
    
    void teardown()
    {
        delete astFunc->body;
        delete astFunc;
        mock().clear();
    }
};

TEST(ParseFunction, get_string)
{
    std::string input("() 0");
    mock().expectOneCall("parseExpression");
    astFunc = p->parse_function(input.begin());
}

TEST(ParseFunction, Expression)
{
    std::string input("(a) 0");
    mock().expectOneCall("parseExpression");
    astFunc = p->parse_function(input.begin());
}

TEST(ParseFunction, Compound)
{
    std::string input("(a) {\na\nb\n}");
    mock().expectOneCall("parseCompound");
    astFunc = p->parse_function(input.begin());
}
