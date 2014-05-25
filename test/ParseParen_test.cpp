#include <iostream>
#include <CppUTest/TestHarness.h>

#include "../src/parser.h"

TEST_GROUP(ParseParen)
{
};

TEST(ParseParen, ReturnElement)
{
    ParseParen p;
    AstNode *term = p.parse_paren("(1)");
    CHECK_EQUAL(AST_ELEMENT, term->type);
    delete term;
}
