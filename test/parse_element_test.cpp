#include <CppUTest/TestHarness.h>
#include <limits.h>

#include "../src/parser.h"

TEST_GROUP(parse_element)
{
};

TEST(parse_element, CanHaveNumber)
{
    AstNode *elem = parse_element("1");
    AstNode *num = elem->children.at(0);
    CHECK_EQUAL(AST_NUMBER, num->type);
    delete elem;
}

TEST(parse_element, CanHaveParen)
{
    AstNode *elem = parse_element("(1)");
    AstNode *num = elem->children.at(0);
    CHECK_EQUAL(AST_PAREN, num->type);
    delete elem;
}
