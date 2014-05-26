#include <CppUTest/TestHarness.h>

#include "parser/Parse.h"

TEST_GROUP(Parser)
{
};

TEST(Parser, EmptyStatementForEmptyString)
{
	Parse p;
    AstNode *stmt = p.parse("");
    CHECK_EQUAL(NULL, stmt);
}
