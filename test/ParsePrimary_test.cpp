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

TEST(ParsePrimary, 0ArgInvocation)
{
    ParsePrimary p;
    AstInvocation *invoke = dynamic_cast<AstInvocation*>(p.parse_primary("log()"));
    CHECK(invoke);

    delete invoke;
}

TEST(ParsePrimary, 0ArgInvocationWhitespace)
{
    ParsePrimary p;
    AstInvocation *invoke = dynamic_cast<AstInvocation*>(p.parse_primary("log ( )"));
    CHECK(invoke);

    delete invoke;
}

TEST(ParsePrimary, 1ArgInvocation)
{
    ParsePrimary p;
    AstInvocation *invoke = dynamic_cast<AstInvocation*>(p.parse_primary("log(1)"));
    CHECK(invoke);

    delete invoke;
}

TEST(ParsePrimary, 1ArgInvocationWhitespace)
{
    ParsePrimary p;
    AstInvocation *invoke = dynamic_cast<AstInvocation*>(p.parse_primary("log ( 1 )"));
    CHECK(invoke);

    delete invoke;
}

TEST(ParsePrimary, 2ArgInvocation)
{
    ParsePrimary p;
    AstInvocation *invoke = dynamic_cast<AstInvocation*>(p.parse_primary("log(1,2)"));
    CHECK(invoke);

    delete invoke;
}

TEST(ParsePrimary, 2ArgInvocationWhitespace)
{
    ParsePrimary p;
    AstNode *node = p.parse_primary("log ( 1 , 2 )");
    AstInvocation *invoke = dynamic_cast<AstInvocation*>(node);
    CHECK(invoke);

    delete invoke;
}
