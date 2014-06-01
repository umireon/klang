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

TEST(ParseIdentifier, ReturnIdentifierNode)
{
    std::string input("a");
    ident = p.parse_identifier(input.begin());
    CHECK(ident);
    CHECK_EQUAL(input, ident->get_string());
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
