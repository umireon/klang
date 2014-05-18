#include <iostream>
#include <CppUTest/TestHarness.h>

#include "../src/parser.h"

TEST_GROUP(parse_term)
{
};

/*TEST(parse_term, ReturnTermNode)
{
    struct ast_node *term;
    term = parse_term("1");
    CHECK_EQUAL(AST_TERM, term->type);
}

TEST(parse_term, CanHaveAPlainNumber)
{
    struct ast_node *term, *num;
    term = parse_term("0x5");
    CHECK_EQUAL(1, term->num_of_child);

    num = term->children[0];
    CHECK_EQUAL(AST_NUMBER, num->type);
    CHECK_EQUAL(5, num->value);
}

TEST(parse_term, CanHaveAPositiveNumber)
{
    struct ast_node *term, *num;
    term = parse_term("+-+-+0x5");
    CHECK_EQUAL(1, term->num_of_child);

    num = term->children[0];
    CHECK_EQUAL(AST_NUMBER, num->type);
    CHECK_EQUAL(5, num->value);
}


TEST(parse_term, CanHaveANegativeNumber)
{
    struct ast_node *term, *num;
    term = parse_term("-+-+-0x5");
    CHECK_EQUAL(1, num->num_of_child);

    num = term->children[0];
    CHECK_EQUAL(AST_NUMBER, num->type);
    CHECK_EQUAL(-5, num->value);
}

TEST(parse_term, 2ElemMultiplication)
{
    struct ast_node *term, *mul, *num;
    term = parse_term("2*3");
    CHECK_EQUAL(1, term->num_of_child);

    mul = term->children[0];
    CHECK_EQUAL(AST_MULTIPLICATION, mul->type);
    CHECK_EQUAL(2, mul->num_of_child);

    num = mul->children[0];
    CHECK_EQUAL(AST_NUMBER, num->type);
    CHECK_EQUAL(0, num->num_of_child);
    CHECK_EQUAL(2, num->value);

    num = mul->children[1];
    CHECK_EQUAL(AST_NUMBER, num->type);
    CHECK_EQUAL(0, num->num_of_child);
    CHECK_EQUAL(3, num->value);
}

TEST(parse_term, 3ElemMultiplication)
{
    struct ast_node *term, *mul, *num;
    term = parse_term("2*3*4");
    CHECK_EQUAL(1, term->num_of_child);

    mul = term->children[0];
    CHECK_EQUAL(AST_MULTIPLICATION, mul->type);
    CHECK_EQUAL(2, mul->num_of_child);

    num = mul->children[1];
    CHECK_EQUAL(AST_NUMBER, num->type);
    CHECK_EQUAL(0, num->num_of_child);
    CHECK_EQUAL(4, num->value);

    mul = mul->children[0];
    CHECK_EQUAL(AST_MULTIPLICATION, mul->type);
    CHECK_EQUAL(2, mul->num_of_child);

    num = mul->children[1];
    CHECK_EQUAL(AST_NUMBER, num->type);
    CHECK_EQUAL(0, num->num_of_child);
    CHECK_EQUAL(3, num->value);

    num = mul->children[0];
    CHECK_EQUAL(AST_NUMBER, num->type);
    CHECK_EQUAL(0, num->num_of_child);
    CHECK_EQUAL(2, num->value);
}


TEST(parse_term, 2ElemDivision)
{
    struct ast_node *term, *mul, *num;
    term = parse_term("2/3");
    CHECK_EQUAL(1, term->num_of_child);

    mul = term->children[0];
    CHECK_EQUAL(AST_DIVISION, mul->type);
    CHECK_EQUAL(2, mul->num_of_child);

    num = mul->children[0];
    CHECK_EQUAL(AST_NUMBER, num->type);
    CHECK_EQUAL(0, num->num_of_child);
    CHECK_EQUAL(2, num->value);

    num = mul->children[1];
    CHECK_EQUAL(AST_NUMBER, num->type);
    CHECK_EQUAL(0, num->num_of_child);
    CHECK_EQUAL(3, num->value);
}

TEST(parse_term, 3ElemDivision)
{
    struct ast_node *term, *mul, *num;
    term = parse_term("2/3/4");
    CHECK_EQUAL(1, term->num_of_child);

    mul = term->children[0];
    CHECK_EQUAL(AST_DIVISION, mul->type);
    CHECK_EQUAL(2, mul->num_of_child);

    num = mul->children[1];
    CHECK_EQUAL(AST_NUMBER, num->type);
    CHECK_EQUAL(0, num->num_of_child);
    CHECK_EQUAL(4, num->value);

    mul = mul->children[0];
    CHECK_EQUAL(AST_DIVISION, mul->type);
    CHECK_EQUAL(2, mul->num_of_child);

    num = mul->children[1];
    CHECK_EQUAL(AST_NUMBER, num->type);
    CHECK_EQUAL(0, num->num_of_child);
    CHECK_EQUAL(3, num->value);

    num = mul->children[0];
    CHECK_EQUAL(AST_NUMBER, num->type);
    CHECK_EQUAL(0, num->num_of_child);
    CHECK_EQUAL(2, num->value);
}

TEST(parse_term, 3Elem)
{
    struct ast_node *term, *mul, *num;
    term = parse_term("2/3*4");
    CHECK_EQUAL(1, term->num_of_child);

    mul = term->children[0];
    CHECK_EQUAL(AST_MULTIPLICATION, mul->type);
    CHECK_EQUAL(2, mul->num_of_child);

    num = mul->children[1];
    CHECK_EQUAL(AST_NUMBER, num->type);
    CHECK_EQUAL(0, num->num_of_child);
    CHECK_EQUAL(4, num->value);

    mul = mul->children[0];
    CHECK_EQUAL(AST_DIVISION, mul->type);
    CHECK_EQUAL(2, mul->num_of_child);

    num = mul->children[1];
    CHECK_EQUAL(AST_NUMBER, num->type);
    CHECK_EQUAL(0, num->num_of_child);
    CHECK_EQUAL(3, num->value);

    num = mul->children[0];
    CHECK_EQUAL(AST_NUMBER, num->type);
    CHECK_EQUAL(0, num->num_of_child);
    CHECK_EQUAL(2, num->value);
}*/
