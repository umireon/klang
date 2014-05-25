#include <CppUTest/TestHarness.h>
#include <limits.h>

#include "../src/parser.h"

TEST_GROUP(ParseIdentifier)
{
};

TEST(ParseIdentifier, ReturnIdentifierNode)
{
    ParseIdentifier p;
    AstNode *ident;
    ident = p.parse_identifier("a");
    CHECK_EQUAL(AST_IDENTIFIER, ident->type);
    delete ident;
}

TEST(ParseIdentifier, CanRead4LetterIdentifier)
{
    ParseIdentifier p;
    AstNode *ident;
    ident = p.parse_identifier("abcd");
    CHECK_EQUAL(AST_IDENTIFIER, ident->type);
    CHECK_EQUAL(4, ident->strtail - ident->strhead);

    delete ident;
}

TEST(ParseIdentifier, CanRead4AlnumIdentifier)
{
    ParseIdentifier p;
    AstNode *ident;
    ident = p.parse_identifier("a2xd");
    CHECK_EQUAL(AST_IDENTIFIER, ident->type);
    CHECK_EQUAL(4, ident->strtail - ident->strhead);

    delete ident;
}