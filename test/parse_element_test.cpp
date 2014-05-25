#include <CppUTest/TestHarness.h>
#include <limits.h>

#include "../src/parser.h"

TEST_GROUP(parse_element)
{
};
/*
TEST(parse_element, CanHaveNumber)
{
	Parse p;
    AstNode *elem = p.parse_element("1");
    AstNode *num = elem->children.at(0);
    CHECK_EQUAL(AST_NUMBER, num->type);
    delete elem;
}

TEST(parse_element, CanHaveParen)
{
	Parse p;
    AstNode *elem = p.parse_element("(1)");
    AstNode *num = elem->children.at(0);
    CHECK_EQUAL(AST_PAREN, num->type);
    delete elem;
}
*/