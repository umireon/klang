#include <iostream>
#include <CppUTest/TestHarness.h>

extern "C" {
#include "../src/parser.h"
}

void print_ast(struct ast_node *root, int depth)
{
    for (int i = 0; i < depth; i++) {
        std::cout << "  ";
    }

    switch (root->type) {
    case AST_NUMBER:
        std::cout << "<AST_NUMBER: ";
        break;
    case AST_TERM:
        std::cout << "<AST_TERM: ";
        break;
    case AST_MULTIPLICATION:
        std::cout << "<AST_MULTIPLICATION: ";
        break;
    case AST_STATEMENT:
        std::cout << "<AST_STATEMENT: ";
        break;
    }

    std::cout << root->value << std::endl;

    for (int i = 0; i < root->num_of_child; i++) {
        print_ast(root->children[i], depth + 1);
    }
}

TEST_GROUP(parse_term)
{
};

TEST(parse_term, ReturnTermNode)
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

TEST(parse_term, CanHave2TermMultiplication)
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

TEST(parse_term, CanHave3TermMultiplication)
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
