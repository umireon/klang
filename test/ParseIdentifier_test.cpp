#include <CppUTest/TestHarness.h>
#include <limits.h>

#include "parser.h"

TEST_GROUP(ParseIdentifier)
{
    ParseIdentifier p;
    AstNode *node;
    AstIdentifier *ident;

    void teardown()
    {
        delete node;
    }
};

TEST(ParseIdentifier, ReturnIdentifierNode)
{
    node = p.parse_identifier("a");
    ident = dynamic_cast<AstIdentifier *>(node);
    CHECK(ident);
    CHECK_EQUAL("a", ident->get_string());
}

TEST(ParseIdentifier, CanRead4LetterIdentifier)
{
    node = p.parse_identifier("abcd");
    ident = dynamic_cast<AstIdentifier *>(node);
    CHECK(ident);
    CHECK_EQUAL("abcd", ident->get_string());
}

TEST(ParseIdentifier, CanRead4AlnumIdentifier)
{
    node = p.parse_identifier("a2xd");
    ident = dynamic_cast<AstIdentifier *>(node);
    CHECK(ident);
    CHECK_EQUAL("a2xd", ident->get_string());
}
