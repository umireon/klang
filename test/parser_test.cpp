#include <CppUTest/TestHarness.h>

#include "parser.h"

TEST_GROUP(Parser)
{
};

TEST(Parser, EmptyStatementForEmptyString)
{
	Parse p;
    AstNode *stmt = p.parse("");
    CHECK_EQUAL(NULL, stmt);
}
