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

    stmt = parse_number("11");
    CHECK_EQUAL(11, stmt->value);

    stmt = parse_number("121");
    CHECK_EQUAL(121, stmt->value);
}


TEST(Parser, ParseHex)
{
    struct ast_node *stmt;
    stmt = parse_number("0xA");
    CHECK_EQUAL(AST_NUMBER, stmt->type);
    CHECK_EQUAL(0, stmt->num_of_child);
    CHECK_EQUAL(0xA, stmt->value);

    stmt = parse_number("0xF5");
    CHECK_EQUAL(0xF5, stmt->value);

    stmt = parse_number("0Xf5");
    CHECK_EQUAL(0xF5, stmt->value);
}

TEST(Parser, ParseOct)
{
    struct ast_node *stmt;
    stmt = parse_number("03");
    CHECK_EQUAL(AST_NUMBER, stmt->type);
    CHECK_EQUAL(0, stmt->num_of_child);
    CHECK_EQUAL(3, stmt->value);

    stmt = parse_number("010");
    CHECK_EQUAL(010, stmt->value);

    stmt = parse_number("0");
    CHECK_EQUAL(0, stmt->value);
}
