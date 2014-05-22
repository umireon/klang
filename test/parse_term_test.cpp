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
}

TEST(parse_term, ContainsElement)
{
    AstNode *term = parse_term("0x5");
    CHECK_EQUAL(1, term->children.size());

    AstNode *elem = term->children.at(0);
    CHECK_EQUAL(AST_ELEMENT, elem->type);

    delete term;
}

TEST(parse_term, 2ElemMultiplication)
{
    AstNode *term = parse_term("2*3");
    CHECK_EQUAL(1, term->children.size());

    AstNode *mul = term->children.at(0);
    CHECK_EQUAL(AST_MULTIPLICATION, mul->type);
    CHECK_EQUAL(2, mul->children.size());

    delete term;
}

TEST(parse_term, 3ElemMultiplication)
{
    AstNode *term = parse_term("2*3*4");
    CHECK_EQUAL(1, term->children.size());

    AstNode *mul1 = term->children.at(0);
    CHECK_EQUAL(AST_MULTIPLICATION, mul1->type);
    CHECK_EQUAL(2, mul1->children.size());

    AstNode *mul2 = mul1->children.at(0);
    CHECK_EQUAL(AST_MULTIPLICATION, mul2->type);
    CHECK_EQUAL(2, mul2->children.size());

    delete term;
}


TEST(parse_term, 2ElemDivision)
{
    AstNode *term = parse_term("2/3");
    CHECK_EQUAL(1, term->children.size());

    AstNode *div = term->children.at(0);
    CHECK_EQUAL(AST_DIVISION, div->type);
    CHECK_EQUAL(2, div->children.size());

    delete term;
}

TEST(parse_term, 3ElemDivision)
{
    AstNode *term = parse_term("2/3/4");
    CHECK_EQUAL(1, term->children.size());

    AstNode *div1 = term->children.at(0);
    CHECK_EQUAL(AST_DIVISION, div1->type);
    CHECK_EQUAL(2, div1->children.size());

    AstNode *div2 = div1->children.at(0);
    CHECK_EQUAL(AST_DIVISION, div2->type);
    CHECK_EQUAL(2, div2->children.size());

    delete term;
}

TEST(parse_term, 3ElemComplex)
{
    AstNode *term = parse_term("2/3*4");
    CHECK_EQUAL(1, term->children.size());

    AstNode *mul = term->children.at(0);
    CHECK_EQUAL(AST_MULTIPLICATION, mul->type);
    CHECK_EQUAL(2, mul->children.size());

    AstNode *div = mul->children.at(0);
    CHECK_EQUAL(AST_DIVISION, div->type);
    CHECK_EQUAL(2, div->children.size());

    delete term;
}
