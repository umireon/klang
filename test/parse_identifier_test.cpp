#include <CppUTest/TestHarness.h>
#include <limits.h>

#include "../src/parser.h"

TEST_GROUP(parse_identifier)
{
};

TEST(parse_identifier, ReturnIdentifierNode)
{
    Parse p;
    AstNode *ident;
    ident = p.parse_identifier("a");
    CHECK_EQUAL(AST_IDENTIFIER, ident->type);
    delete ident;
}

TEST(parse_identifier, CanRead4LetterIdentifier)
{
    Parse p;
    AstNode *ident;
    ident = p.parse_identifier("abcd");
    CHECK_EQUAL(AST_IDENTIFIER, ident->type);
    CHECK_EQUAL(4, ident->strtail - ident->strhead);

    delete ident;
}

TEST(parse_identifier, CanRead4AlnumIdentifier)
{
    Parse p;
    AstNode *ident;
    ident = p.parse_identifier("a2xd");
    CHECK_EQUAL(AST_IDENTIFIER, ident->type);
    CHECK_EQUAL(4, ident->strtail - ident->strhead);

    delete ident;
}