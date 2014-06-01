#include <CppUTest/TestHarness.h>

#include <string>

#include "ast/AstParen.h"

#include "parser/ParseParen.h"

TEST_GROUP(ParseParen)
{
    ParseParen p;
    AstParen *paren;
    
    void teardown()
    {
        delete paren;
    }
};

TEST(ParseParen, get_string)
{
    std::string input("(1)");
    paren = p.parse_paren(input.begin());
    CHECK_EQUAL(input, paren->get_string());
}

TEST(ParseParen, Number)
{
    std::string input("(1)");
    paren = p.parse_paren(input.begin());
    CHECK_EQUAL(std::string("1"), paren->children.at(0)->get_string());
}

TEST(ParseParen, NumberWhitespace)
{
    std::string input("( 1 )");
    paren = p.parse_paren(input.begin());
    CHECK_EQUAL(std::string("1"), paren->children.at(0)->get_string());
}

TEST(ParseParen, Identity)
{
    std::string input("(a)");
    paren = p.parse_paren(input.begin());
    CHECK_EQUAL(std::string("a"), paren->children.at(0)->get_string());
}

TEST(ParseParen, IdentityWhitespace)
{
    std::string input("( a )");
    paren = p.parse_paren(input.begin());
    CHECK_EQUAL(std::string("a"), paren->children.at(0)->get_string());
}

TEST(ParseParen, NestedParen)
{
    std::string input("((1))");
    paren = p.parse_paren(input.begin());
    
    AstParen *paren0 = dynamic_cast<AstParen*>(paren->children.at(0));
    CHECK(paren0);
    
    CHECK_EQUAL(std::string("1"), paren0->children.at(0)->get_string());
}

TEST(ParseParen, NestedParenWhitespace)
{
    std::string input("(  ( 1 ) )");
    paren = p.parse_paren(input.begin());
    
    AstParen *paren0 = dynamic_cast<AstParen*>(paren->children.at(0));
    CHECK(paren0);
    
    CHECK_EQUAL(std::string("1"), paren0->children.at(0)->get_string());
}
