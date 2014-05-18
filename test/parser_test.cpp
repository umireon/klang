#include <CppUTest/TestHarness.h>

#include "../src/parser.h"

TEST_GROUP(Parser)
{
};

TEST(Parser, EmptyStatementForEmptyString)
{
    AstNode *stmt = parse("");
    CHECK_EQUAL(AST_STATEMENT, stmt->type);
    CHECK(stmt->children.empty());
    delete stmt;
}
