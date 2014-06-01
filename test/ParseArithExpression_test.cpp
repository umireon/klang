#include <CppUTest/TestHarness.h>

#include <stdexcept>
#include <string>
#include <memory>

#include "ast/AstNumber.h"
#include "ast/AstAddition.h"
#include "ast/AstSubtraction.h"

#include "parser/ParseArithExpression.h"

TEST_GROUP(ParseArithExpression)
{
    ParseArithExpression p;
    AstNode *node;
    
    void teardown()
    {
        delete node;
    }
};

TEST(ParseArithExpression, get_string)
{
    std::string input("0");
    node = p.parse_arith_expression(input.begin());
    CHECK_EQUAL(input, node->get_string());
}

TEST(ParseArithExpression, invalsid_starting)
{
    std::string input(" ");
    CHECK_THROWS(std::invalid_argument, p.parse_arith_expression(input.begin()));
}

TEST(ParseArithExpression, AstNumber)
{
    std::string input("0");
    node = p.parse_arith_expression(input.begin());
    AstNumber *num = dynamic_cast<AstNumber *>(node);
    CHECK(num);
    CHECK_EQUAL(input, num->get_string());
}

TEST(ParseArithExpression, 2ElemAddition)
{
    std::string input("2+3");
    node = p.parse_arith_expression(input.begin());
    AstAddition *expr = dynamic_cast<AstAddition *>(node);
    CHECK(expr);
    std::vector<AstNode *> &children = expr->children;
    
    CHECK_EQUAL(std::string("2"), children[0]->get_string());
    CHECK_EQUAL(std::string("3"), children[1]->get_string());
}

TEST(ParseArithExpression, 3ElemAddition)
{
    std::string input("2+3+4");
    node = p.parse_arith_expression(input.begin());
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
    node = p.parse_arith_expression(input.begin());
    AstSubtraction *expr = dynamic_cast<AstSubtraction *>(node);
    CHECK(expr);
    std::vector<AstNode *> &children = expr->children;
    
    CHECK_EQUAL(std::string("2"), children[0]->get_string());
    CHECK_EQUAL(std::string("3"), children[1]->get_string());
}

TEST(ParseArithExpression, 3ElemSubtraction)
{
    std::string input("2-3-4");
    node = p.parse_arith_expression(input.begin());
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
    node = p.parse_arith_expression(input.begin());
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
    std::string input("2 + 3 - 4");
    node = p.parse_arith_expression(input.begin());
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

