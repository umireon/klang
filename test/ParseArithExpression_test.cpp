#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

#include <string>

#include "ast/AstNumber.h"
#include "ast/AstAddition.h"
#include "ast/AstSubtraction.h"

#include "parser/types.h"
#include "parser/BaseParse.h"
#include "parser/ParseArithExpression.h"

TEST_GROUP(ParseArithExpression)
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

    ParseArithExpression parseArithExpression, *p;

    AstNode *node;
    
    void setup()
    {
        p = &parseArithExpression;
        p->parseNext = &parseNextMock;
    }
    
    void teardown()
    {
        delete node;
        mock().clear();
    }
};

TEST(ParseArithExpression, get_string)
{
    std::string input("0");
    mock().expectOneCall("parse");
    node = p->parse_arith_expression(input.begin());
    CHECK_EQUAL(input, node->get_string());
}

TEST(ParseArithExpression, 2ElemAddition)
{
    std::string input("2+3");
    mock().expectNCalls(2, "parse");
    node = p->parse_arith_expression(input.begin());
    AstAddition *expr = dynamic_cast<AstAddition *>(node);
    CHECK(expr);
    std::vector<AstNode *> &children = expr->children;
    
    CHECK_EQUAL(std::string("2"), children[0]->get_string());
    CHECK_EQUAL(std::string("3"), children[1]->get_string());
}

TEST(ParseArithExpression, 3ElemAddition)
{
    std::string input("2+3+4");
    mock().expectNCalls(3, "parse");
    node = p->parse_arith_expression(input.begin());
    AstAddition *expr = dynamic_cast<AstAddition *>(node);
    CHECK(expr);
    std::vector<AstNode *> &children = expr->children;
    
    AstAddition *expr0 = dynamic_cast<AstAddition *>(children[0]);
    CHECK(expr0);
    std::vector<AstNode *> &children0 = expr0->children;
    
    CHECK_EQUAL(std::string("2"), children0[0]->get_string());
    CHECK_EQUAL(std::string("3"), children0[1]->get_string());
    CHECK_EQUAL(std::string("4"), children[1]->get_string());
}

TEST(ParseArithExpression, 2ElemSubtraction)
{
    std::string input("2-3");
    mock().expectNCalls(2, "parse");
    node = p->parse_arith_expression(input.begin());
    AstSubtraction *expr = dynamic_cast<AstSubtraction *>(node);
    CHECK(expr);
    std::vector<AstNode *> &children = expr->children;
    
    CHECK_EQUAL(std::string("2"), children[0]->get_string());
    CHECK_EQUAL(std::string("3"), children[1]->get_string());
}

TEST(ParseArithExpression, 3ElemSubtraction)
{
    std::string input("2-3-4");
    mock().expectNCalls(3, "parse");
    node = p->parse_arith_expression(input.begin());
    AstSubtraction *expr = dynamic_cast<AstSubtraction *>(node);
    CHECK(expr);
    std::vector<AstNode *> &children = expr->children;
    
    AstSubtraction *expr0 = dynamic_cast<AstSubtraction *>(children[0]);
    CHECK(expr0);
    std::vector<AstNode *> &children0 = expr0->children;
    
    CHECK_EQUAL(std::string("2"), children0[0]->get_string());
    CHECK_EQUAL(std::string("3"), children0[1]->get_string());
    CHECK_EQUAL(std::string("4"), children[1]->get_string());
}

TEST(ParseArithExpression, Complex)
{
    std::string input("2+3-4");
    mock().expectNCalls(3, "parse");
    node = p->parse_arith_expression(input.begin());
    AstSubtraction *expr = dynamic_cast<AstSubtraction *>(node);
    CHECK(expr);
    std::vector<AstNode *> &children = expr->children;
    
    AstAddition *expr0 = dynamic_cast<AstAddition *>(children[0]);
    CHECK(expr0);
    std::vector<AstNode *> &children0 = expr0->children;
    
    CHECK_EQUAL(std::string("2"), children0[0]->get_string());
    CHECK_EQUAL(std::string("3"), children0[1]->get_string());
    CHECK_EQUAL(std::string("4"), children[1]->get_string());
}

TEST(ParseArithExpression, Whitespace)
{
    std::string input("2 +  3   - 4");
    mock().expectNCalls(3, "parse");
    node = p->parse_arith_expression(input.begin());
    AstSubtraction *expr = dynamic_cast<AstSubtraction *>(node);
    CHECK(expr);
    std::vector<AstNode *> &children = expr->children;
    
    AstAddition *expr0 = dynamic_cast<AstAddition *>(children[0]);
    CHECK(expr0);
    std::vector<AstNode *> &children0 = expr0->children;
    
    CHECK_EQUAL(std::string("2"), children0[0]->get_string());
    CHECK_EQUAL(std::string("3"), children0[1]->get_string());
    CHECK_EQUAL(std::string("4"), children[1]->get_string());
}

