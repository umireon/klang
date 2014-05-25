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
    AstNode *paren = p.parse_paren("(1)");
    CHECK_EQUAL(1, paren->get_long());
    delete paren;
}

TEST(ParseParen, NumberWhitespace)
{
    ParseParen p;
    AstNode *paren = p.parse_paren("( 1 )");
    CHECK_EQUAL(1, paren->get_long());
    delete paren;
}

TEST(ParseParen, Identity)
{
    ParseParen p;
    AstParen *paren = p.parse_paren("(a)");
    CHECK_EQUAL(std::string("a"), paren->children[0]->get_string());
    delete paren;
}

TEST(ParseParen, IdentityWhitespace)
{
    ParseParen p;
    AstParen *paren = p.parse_paren("( a )");
    CHECK_EQUAL(std::string("a"), paren->children[0]->get_string());
    delete paren;
}

TEST(ParseParen, NestedParen)
{
    ParseParen p;
    AstNode *paren = p.parse_paren("((1))");
    CHECK_EQUAL(1, paren->get_long());
    delete paren;
}

TEST(ParseParen, NestedParenWhitespace)
{
    ParseParen p;
    AstNode *paren = p.parse_paren("( ( 1 ) )");
    CHECK_EQUAL(1, paren->get_long());
    delete paren;
}
