#include <iostream>
#include <CppUTest/TestHarness.h>

#include "../src/Parse.h"
#include "../src/ast.h"

TEST_GROUP(ParseParen)
{
};

TEST(ParseParen, Number)
{
    ParseParen p;
    AstNode *expr = p.parse_paren("(1)");
    CHECK_EQUAL(1, expr->get_long());
    delete expr;
}

TEST(ParseParen, Identity)
{
    ParseParen p;
    AstNode *expr = p.parse_paren("(a)");
    CHECK_EQUAL(1, expr->size());
    CHECK_EQUAL(std::string("a"), expr->children[0]->get_string());
    delete expr;
}

TEST(ParseParen, NestedParen)
{
    ParseParen p;
    AstNode *expr = p.parse_paren("((1))");
    CHECK_EQUAL(1, expr->get_long());
    delete expr;
}
