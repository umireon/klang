#include <iostream>
#include <CppUTest/TestHarness.h>

#include "../src/parser.h"

TEST_GROUP(parse_expression)
{
};

TEST(parse_expression, ReturnExpressionNode)
{
    Parse p;
    AstNode *expr = p.parse_expression("1");
    CHECK_EQUAL(AST_EXPRESSION, expr->type);
    delete expr;
}

TEST(parse_expression, 2TermAddition)
{
    Parse p;
    AstNode *expr = p.parse_expression("2+3");
    AstNode *add = expr->children.at(0);

    CHECK_EQUAL(AST_ADDITION, add->type);
    CHECK_EQUAL(2, add->children.size());

    delete expr;
}

TEST(parse_expression, 3TermAddition)
{
    Parse p;
    AstNode *expr = p.parse_expression("2+3+4");
    AstNode *add1 = expr->children.at(0);
    AstNode *add2 = add1->children.at(0);

    CHECK_EQUAL(AST_ADDITION, add1->type);
    CHECK_EQUAL(2, add1->children.size());
    CHECK_EQUAL(AST_ADDITION, add2->type);
    CHECK_EQUAL(2, add2->children.size());

    delete expr;
}

TEST(parse_expression, 2TermSubtraction)
{
    Parse p;
    AstNode *expr = p.parse_expression("2-3");
    AstNode *sub = expr->children.at(0);

    CHECK_EQUAL(AST_SUBTRACTION, sub->type);
    CHECK_EQUAL(2, sub->children.size());

    delete expr;
}

TEST(parse_expression, 3TermSubtraction)
{
    Parse p;
    AstNode *expr = p.parse_expression("2-3-4");
    AstNode *sub1 = expr->children.at(0);
    AstNode *sub2 = sub1->children.at(0);

    CHECK_EQUAL(AST_SUBTRACTION, sub1->type);
    CHECK_EQUAL(2, sub1->children.size());
    CHECK_EQUAL(AST_SUBTRACTION, sub2->type);
    CHECK_EQUAL(2, sub2->children.size());

    delete expr;
}

TEST(parse_expression, 3ElemComplex)
{
    Parse p;
    AstNode *expr = p.parse_expression("2-3+4");
    CHECK_EQUAL(1, expr->children.size());

    AstNode *add = expr->children.at(0);
    CHECK_EQUAL(AST_ADDITION, add->type);
    CHECK_EQUAL(2, add->children.size());

    AstNode *sub = add->children.at(0);
    CHECK_EQUAL(AST_SUBTRACTION, sub->type);
    CHECK_EQUAL(2, sub->children.size());

    delete expr;
}