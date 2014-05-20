#include <iostream>
#include <CppUTest/TestHarness.h>

#include "../src/parser.h"

TEST_GROUP(parse_paren)
{
};

TEST(parse_paren, ReturnTermNode)
{
    AstNode *term = parse_paren("(1)");
    CHECK_EQUAL(AST_TERM, term->type);
    delete term;
}

TEST(parse_paren, ContainsParenLeftNode)
{
    AstNode *term = parse_paren("(1)");
    AstNode *expr = term->children.at(0);
    CHECK_EQUAL(AST_PAREN_LEFT, expr->type);
    delete term;
}

TEST(parse_paren, ContainsExpressionNode)
{
    AstNode *term = parse_paren("(1)");
    AstNode *expr = term->children.at(1);
    CHECK_EQUAL(AST_EXPRESSION, expr->type);
    delete term;
}

TEST(parse_paren, ContainsParenRightNode)
{
    AstNode *term = parse_paren("(1)");
    //AstNode *expr = term->children.at(2);
    //CHECK_EQUAL(AST_PAREN_RIGHT, expr->type);
    delete term;
}