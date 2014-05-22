#include <iostream>
#include <CppUTest/TestHarness.h>

#include "../src/parser.h"

TEST_GROUP(parse_term)
{
};

TEST(parse_term, ReturnTermNode)
{
    AstNode *term = parse_term("1");
    CHECK_EQUAL(AST_TERM, term->type);
    delete term;
}/*

TEST(parse_term, CanHaveAPlainNumber)
{
    AstNode *term = parse_term("0x5");
    CHECK_EQUAL(1, term->children.size());

    AstNode *num = term->children.at(0);
    CHECK_EQUAL(AST_NUMBER, num->type);
    CHECK_EQUAL(5, num->value);
    delete term;
}

TEST(parse_term, CanHaveAPositiveNumber)
{
    AstNode *term = parse_term("+-+-+0x5");
    CHECK_EQUAL(1, term->children.size());

    AstNode *num = term->children.at(0);
    CHECK_EQUAL(AST_NUMBER, num->type);
    CHECK_EQUAL(5, num->value);
    delete term;
}


TEST(parse_term, CanHaveANegativeNumber)
{
    AstNode *term = parse_term("-+-+-0x5");
    CHECK_EQUAL(1, term->children.size());

    AstNode *num = term->children.at(0);
    CHECK_EQUAL(AST_NUMBER, num->type);
    CHECK_EQUAL(-5, num->value);
    delete term;
}

TEST(parse_term, 2ElemMultiplication)
{
    AstNode *term = parse_term("2*3");
    CHECK_EQUAL(1, term->children.size());

    AstNode *mul = term->children.at(0);
    CHECK_EQUAL(AST_MULTIPLICATION, mul->type);
    CHECK_EQUAL(2, mul->children.size());

    AstNode *num1 = mul->children.at(0);
    CHECK_EQUAL(AST_NUMBER, num1->type);
    CHECK_EQUAL(0, num1->children.size());
    CHECK_EQUAL(2, num1->value);

    AstNode *num2 = mul->children.at(1);
    CHECK_EQUAL(AST_NUMBER, num2->type);
    CHECK_EQUAL(0, num2->children.size());
    CHECK_EQUAL(3, num2->value);
    delete term;
}

TEST(parse_term, 3ElemMultiplication)
{
    AstNode *term = parse_term("2*3*4");
    CHECK_EQUAL(1, term->children.size());

    AstNode *mul1 = term->children.at(0);
    CHECK_EQUAL(AST_MULTIPLICATION, mul1->type);
    CHECK_EQUAL(2, mul1->children.size());

    AstNode *num1 = mul1->children.at(1);
    CHECK_EQUAL(AST_NUMBER, num1->type);
    CHECK_EQUAL(0, num1->children.size());
    CHECK_EQUAL(4, num1->value);

    AstNode *mul2 = mul1->children.at(0);
    CHECK_EQUAL(AST_MULTIPLICATION, mul2->type);
    CHECK_EQUAL(2, mul2->children.size());

    AstNode *num2 = mul2->children.at(1);
    CHECK_EQUAL(AST_NUMBER, num2->type);
    CHECK_EQUAL(0, num2->children.size());
    CHECK_EQUAL(3, num2->value);

    AstNode *num3 = mul2->children.at(0);
    CHECK_EQUAL(AST_NUMBER, num3->type);
    CHECK_EQUAL(0, num3->children.size());
    CHECK_EQUAL(2, num3->value);
    delete term;
}


TEST(parse_term, 2ElemDivision)
{
    AstNode *term = parse_term("2/3");
    CHECK_EQUAL(1, term->children.size());

    AstNode *div = term->children.at(0);
    CHECK_EQUAL(AST_DIVISION, div->type);
    CHECK_EQUAL(2, div->children.size());

    AstNode *num1 = div->children.at(0);
    CHECK_EQUAL(AST_NUMBER, num1->type);
    CHECK_EQUAL(0, num1->children.size());
    CHECK_EQUAL(2, num1->value);

    AstNode *num2 = div->children.at(1);
    CHECK_EQUAL(AST_NUMBER, num2->type);
    CHECK_EQUAL(0, num2->children.size());
    CHECK_EQUAL(3, num2->value);
    delete term;
}

TEST(parse_term, 3ElemDivision)
{
    AstNode *term = parse_term("2/3/4");
    CHECK_EQUAL(1, term->children.size());

    AstNode *div1 = term->children.at(0);
    CHECK_EQUAL(AST_DIVISION, div1->type);
    CHECK_EQUAL(2, div1->children.size());

    AstNode *num1 = div1->children.at(1);
    CHECK_EQUAL(AST_NUMBER, num1->type);
    CHECK_EQUAL(0, num1->children.size());
    CHECK_EQUAL(4, num1->value);

    AstNode *div2 = div1->children.at(0);
    CHECK_EQUAL(AST_DIVISION, div2->type);
    CHECK_EQUAL(2, div2->children.size());

    AstNode *num2 = div2->children.at(1);
    CHECK_EQUAL(AST_NUMBER, num2->type);
    CHECK_EQUAL(0, num2->children.size());
    CHECK_EQUAL(3, num2->value);

    AstNode *num3 = div2->children.at(0);
    CHECK_EQUAL(AST_NUMBER, num3->type);
    CHECK_EQUAL(0, num3->children.size());
    CHECK_EQUAL(2, num3->value);
    delete term;
}

TEST(parse_term, 3Elem)
{
    AstNode *term = parse_term("2/3*4");
    CHECK_EQUAL(1, term->children.size());

    AstNode *mul = term->children.at(0);
    CHECK_EQUAL(AST_MULTIPLICATION, mul->type);
    CHECK_EQUAL(2, mul->children.size());

    AstNode *num1 = mul->children.at(1);
    CHECK_EQUAL(AST_NUMBER, num1->type);
    CHECK_EQUAL(0, num1->children.size());
    CHECK_EQUAL(4, num1->value);

    AstNode *div = mul->children.at(0);
    CHECK_EQUAL(AST_DIVISION, div->type);
    CHECK_EQUAL(2, div->children.size());

    AstNode *num2 = div->children.at(1);
    CHECK_EQUAL(AST_NUMBER, num2->type);
    CHECK_EQUAL(0, num2->children.size());
    CHECK_EQUAL(3, num2->value);

    AstNode *num3 = div->children.at(0);
    CHECK_EQUAL(AST_NUMBER, num3->type);
    CHECK_EQUAL(0, num3->children.size());
    CHECK_EQUAL(2, num3->value);
    delete term;
}*/
