#include <CppUTest/TestHarness.h>

#include <string>

#include "ast/AstIdentifier.h"

#include "parser/ParseIdentifier.h"

TEST_GROUP(ParseIdentifier)
{
    ParseIdentifier p;
    AstIdentifier *ident;
    
    void teardown()
    {
        delete ident;
    }
};

TEST(ParseIdentifier, Name)
{
    std::string input("a");
    ident = p.parse_identifier(input.begin());
    CHECK(ident);
    CHECK_EQUAL(AstIdentifier::NAME, ident->get_identifier_type());
}

TEST(ParseIdentifier, CanRead4LetterIdentifier)
{
    std::string input("abcd");
    ident = p.parse_identifier(input.begin());
    CHECK(ident);
    CHECK_EQUAL(input, ident->get_string());
}

TEST(ParseIdentifier, CanRead4AlnumIdentifier)
{
    std::string input("a2xd");
    ident = p.parse_identifier(input.begin());
    CHECK(ident);
    CHECK_EQUAL(input, ident->get_string());
}

TEST(ParseIdentifier, ReservedIf)
{
    std::string input("if");
    ident = p.parse_identifier(input.begin());
    CHECK_EQUAL(AstIdentifier::IF, ident->get_identifier_type());
}

TEST(ParseIdentifier, ReservedElsif)
{
    std::string input("elsif");
    ident = p.parse_identifier(input.begin());
    CHECK_EQUAL(AstIdentifier::ELSIF, ident->get_identifier_type());
}

TEST(ParseIdentifier, ReservedElse)
{
    std::string input("else");
    ident = p.parse_identifier(input.begin());
    CHECK_EQUAL(AstIdentifier::ELSE, ident->get_identifier_type());
}
