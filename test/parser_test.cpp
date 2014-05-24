#include <CppUTest/TestHarness.h>

#include "../src/parser.h"

TEST_GROUP(Parser)
{
};

TEST(Parser, EmptyStatementForEmptyString)
{
	Parse p;
    AstNode *stmt = p.parse("");
    CHECK_EQUAL(AST_STATEMENT, stmt->type);
    CHECK(stmt->children.empty());
    delete stmt;
}
