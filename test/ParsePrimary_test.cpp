#include <CppUTest/TestHarness.h>

#include <string>

#include "ast/AstNode.h"
#include "ast/AstNumber.h"
#include "ast/AstIdentifier.h"
#include "ast/AstInvocation.h"
#include "ast/AstParen.h"

#include "parser/ParsePrimary.h"

TEST_GROUP(ParsePrimary)
{
    ParsePrimary p;
    AstNode *node;
    
    void teardown()
    {
        delete node;
    }
};

TEST(ParsePrimary, Number)
{
    std::string input("1");
    node = p.parse_primary(input.begin());
    CHECK(dynamic_cast<AstNumber *>(node));
    CHECK_EQUAL(input, node->get_string());
}

TEST(ParsePrimary, Paren)
{
    std::string input("(1)");
    node = p.parse_primary(input.begin());
    CHECK(dynamic_cast<AstParen *>(node));
    CHECK_EQUAL(input, node->get_string());
}

TEST(ParsePrimary, Identifier)
{
    std::string input("a");
    node = p.parse_primary(input.begin());
    CHECK(dynamic_cast<AstIdentifier *>(node));
    CHECK_EQUAL(input, node->get_string());
}

TEST(ParsePrimary, 0ArgInvocation)
{
    std::string input("log()");
    node = p.parse_primary(input.begin());
    CHECK(dynamic_cast<AstInvocation *>(node));
    CHECK_EQUAL(input, node->get_string());
}

TEST(ParsePrimary, 0ArgInvocationWhitespace)
{
    std::string input("log ( )");
    node = p.parse_primary(input.begin());
    CHECK(dynamic_cast<AstInvocation *>(node));
    CHECK_EQUAL(input, node->get_string());
}

TEST(ParsePrimary, 1ArgInvocation)
{
    std::string input("log(1)");
    node = p.parse_primary(input.begin());
    CHECK(dynamic_cast<AstInvocation *>(node));
    CHECK_EQUAL(input, node->get_string());
}

TEST(ParsePrimary, 1ArgInvocationWhitespace)
{
    std::string input("log ( 1 )");
    node = p.parse_primary(input.begin());
    CHECK(dynamic_cast<AstInvocation *>(node));
    CHECK_EQUAL(input, node->get_string());
}

TEST(ParsePrimary, 2ArgInvocation)
{
    std::string input("log(1,2)");
    node = p.parse_primary(input.begin());
    CHECK(dynamic_cast<AstInvocation *>(node));
    CHECK_EQUAL(input, node->get_string());
}

TEST(ParsePrimary, 2ArgInvocationWhitespace)
{
    std::string input("log  (  1  , 2 )");
    node = p.parse_primary(input.begin());
    CHECK(dynamic_cast<AstInvocation *>(node));
    CHECK_EQUAL(input, node->get_string());
}
