#include <CppUTest/TestHarness.h>

#include "../src/parser.h"

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
