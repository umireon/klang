#include <CppUTest/TestHarness.h>

extern "C" {
#include "../src/parser.h"
}

TEST_GROUP(Parser)
{
};

TEST(Parser, EmptyStatementForEmptyString)
{
    struct ast_node *stmt;
    stmt = parse("");
    CHECK_EQUAL(AST_STATEMENT, stmt->type);
    CHECK_EQUAL(0, stmt->num_of_child);
}

TEST(Parser, ParseDec)
{
    struct ast_node *stmt;
    stmt = parse_number("1");
    CHECK_EQUAL(AST_NUMBER, stmt->type);
    CHECK_EQUAL(0, stmt->num_of_child);
    CHECK_EQUAL(1, stmt->value);
}


TEST(Parser, ParseHex)
{
    struct ast_node *stmt;
    stmt = parse_number("0x2");
    CHECK_EQUAL(AST_NUMBER, stmt->type);
    CHECK_EQUAL(0, stmt->num_of_child);
    CHECK_EQUAL(2, stmt->value);
}

TEST(Parser, ParseOct)
{
    struct ast_node *stmt;
    stmt = parse_number("03");
    CHECK_EQUAL(AST_NUMBER, stmt->type);
    CHECK_EQUAL(0, stmt->num_of_child);
    CHECK_EQUAL(2, stmt->value);
}
