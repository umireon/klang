#include <CppUTest/TestHarness.h>
#include <limits.h>

#include "../src/Parse.h"

TEST_GROUP(ParsePrimary)
{
};

TEST(ParsePrimary, Number)
{
	ParsePrimary p;
    AstNode *prim = p.parse_primary("1");
    CHECK(dynamic_cast<AstNumber*>(prim));

    delete prim;
}

TEST(ParsePrimary, Paren)
{
    ParsePrimary p;
    AstNode *prim = p.parse_primary("(1)");
    CHECK(dynamic_cast<AstParen*>(prim));

    delete prim;
}

TEST(ParsePrimary, Identifier)
{
    ParsePrimary p;
    AstNode *prim = p.parse_primary("a");
    CHECK(dynamic_cast<AstIdentifier*>(prim));

    delete prim;
}
