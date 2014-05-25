#include <iostream>
#include <CppUTest/TestHarness.h>

#include "../src/Parse.h"
#include "../src/ast.h"

using std::string;

TEST_GROUP(ParseParen)
{
};

TEST(ParseParen, Number)
{
    ParseParen p;
    AstParen *paren = p.parse_paren("(1)");
    CHECK_EQUAL(std::string("1"), paren->children.at(0)->get_string());
    delete paren;
}

TEST(ParseParen, NumberWhitespace)
{
    ParseParen p;
    AstParen *paren = p.parse_paren("( 1 )");
    CHECK_EQUAL(std::string("1"), paren->children.at(0)->get_string());
    delete paren;
}

TEST(ParseParen, Identity)
{
    ParseParen p;
    AstParen *paren = p.parse_paren("(a)");
    CHECK_EQUAL(std::string("a"), paren->children.at(0)->get_string());
    delete paren;
}

TEST(ParseParen, IdentityWhitespace)
{
    ParseParen p;
    AstParen *paren = p.parse_paren("( a )");
    CHECK_EQUAL(std::string("a"), paren->children.at(0)->get_string());
    delete paren;
}

TEST(ParseParen, NestedParen)
{
    ParseParen p;
    AstParen *paren = p.parse_paren("((1))");
    
    AstParen *paren0 = dynamic_cast<AstParen*>(paren->children.at(0));
    CHECK(paren0);

    CHECK_EQUAL(string("1"), paren0->children.at(0)->get_string());
    delete paren;
}

TEST(ParseParen, NestedParenWhitespace)
{
    ParseParen p;
    AstParen *paren = p.parse_paren("( ( 1 ) )");
    
    AstParen *paren0 = dynamic_cast<AstParen*>(paren->children.at(0));
    CHECK(paren0);
    
    CHECK_EQUAL(string("1"), paren0->children.at(0)->get_string());
    delete paren;
}
