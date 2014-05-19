#include <iostream>
#include <CppUTest/TestHarness.h>

#include "../src/parser.h"

TEST_GROUP(parse_expression)
{
};

TEST(parse_expression, ReturnExpressionNode)
{
    AstNode *expr = parse_expression("1");
    CHECK_EQUAL(AST_EXPRESSION, expr->type);
    delete expr;
}

TEST(parse_expression, ContainsTermNode)
{
    AstNode *expr = parse_expression("1");
    AstNode *term = expr->children.at(0);
    CHECK_EQUAL(AST_TERM, term->type);
    delete expr;
}

TEST(parse_expression, 2TermAddition)
{
    AstNode *expr = parse_expression("2+3");
    AstNode *add = expr->children.at(0);

    CHECK_EQUAL(AST_ADDITION, add->type);
    CHECK_EQUAL(2, add->children.size());

    AstNode *num1 = add->children.at(0)->children.at(0);
    AstNode *num2 = add->children.at(1)->children.at(0);

    CHECK_EQUAL(2, num1->value);
    CHECK_EQUAL(3, num2->value);

    delete expr;
}

TEST(parse_expression, 3TermAddition)
{
    AstNode *expr = parse_expression("2+3+4");
    AstNode *add1 = expr->children.at(0);
    AstNode *add2 = add1->children.at(0);

    AstNode *num1 = add2->children.at(0)->children.at(0);
    AstNode *num2 = add2->children.at(1)->children.at(0);
    AstNode *num3 = add1->children.at(1)->children.at(0);

    CHECK_EQUAL(2, num1->value);
    CHECK_EQUAL(3, num2->value);
    CHECK_EQUAL(4, num3->value);
    delete expr;
}

TEST(parse_expression, 2TermSubtraction)
{
    AstNode *expr = parse_expression("2-3");
    AstNode *add = expr->children.at(0);

    CHECK_EQUAL(AST_SUBTRACTION, add->type);
    CHECK_EQUAL(2, add->children.size());

    AstNode *num1 = add->children.at(0)->children.at(0);
    AstNode *num2 = add->children.at(1)->children.at(0);

    CHECK_EQUAL(2, num1->value);
    CHECK_EQUAL(3, num2->value);

    delete expr;
}

TEST(parse_expression, 3TermSubtraction)
{
    AstNode *expr = parse_expression("2-3-4");
    AstNode *add1 = expr->children.at(0);
    AstNode *add2 = add1->children.at(0);

    AstNode *num1 = add2->children.at(0)->children.at(0);
    AstNode *num2 = add2->children.at(1)->children.at(0);
    AstNode *num3 = add1->children.at(1)->children.at(0);

    CHECK_EQUAL(2, num1->value);
    CHECK_EQUAL(3, num2->value);
    CHECK_EQUAL(4, num3->value);
    delete expr;
}