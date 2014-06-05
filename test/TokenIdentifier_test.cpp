#include <CppUTest/TestHarness.h>

#include <string>

#include "ast/AstIdentifier.h"

#include "parser/TokenIdentifier.h"

TEST_GROUP(TokenIdentifier)
{
    TokenIdentifier tokenIdentifier, *p;
    SyntaxErrorHandler seh;
    AstIdentifier *ident;
    
    void setup()
    {
        p = &tokenIdentifier;
    }
    
    void teardown()
    {
        delete ident;
    }
};

TEST(TokenIdentifier, Name)
{
    std::string input("a");
    seh.line = &input;
    p->line = &input;
    p->syntaxErrorHandler = &seh;
    ident = p->parse_identifier(input.begin());
    CHECK_EQUAL(AstIdentifier::NAME, ident->get_identifier_type());
}

TEST(TokenIdentifier, CanRead4LetterIdentifier)
{
    std::string input("abcd");
    seh.line = &input;
    p->line = &input;
    p->syntaxErrorHandler = &seh;
    ident = p->parse_identifier(input.begin());
    CHECK_EQUAL(input, ident->get_string());
}

TEST(TokenIdentifier, CanRead4AlnumIdentifier)
{
    std::string input("a2xd");
    seh.line = &input;
    p->line = &input;
    p->syntaxErrorHandler = &seh;
    ident = p->parse_identifier(input.begin());
    CHECK_EQUAL(input, ident->get_string());
}

TEST(TokenIdentifier, ReservedIf)
{
    std::string input("if");
    seh.line = &input;
    p->line = &input;
    p->syntaxErrorHandler = &seh;
    ident = p->parse_identifier(input.begin());
    CHECK_EQUAL(AstIdentifier::IF, ident->get_identifier_type());
}

TEST(TokenIdentifier, ReservedElsif)
{
    std::string input("elsif");
    seh.line = &input;
    p->line = &input;
    p->syntaxErrorHandler = &seh;
    ident = p->parse_identifier(input.begin());
    CHECK_EQUAL(AstIdentifier::ELSIF, ident->get_identifier_type());
}

TEST(TokenIdentifier, ReservedElse)
{
    std::string input("else");
    seh.line = &input;
    p->line = &input;
    p->syntaxErrorHandler = &seh;
    ident = p->parse_identifier(input.begin());
    CHECK_EQUAL(AstIdentifier::ELSE, ident->get_identifier_type());
}
