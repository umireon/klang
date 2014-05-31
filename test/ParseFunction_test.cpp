#include <CppUTest/TestHarness.h>

#include "ast/AstAddition.h"
#include "ast/AstAssignment.h"
#include "ast/AstCompound.h"
#include "ast/AstIdentifier.h"
#include "ast/AstNumber.h"

#include "parser/ParseFunction.h"

TEST_GROUP(ParseFunction)
{
    ParseFunction p;
    AstFunction *astFunc;

    void teardown()
    {
        delete astFunc;
    }
};

TEST(ParseFunction, get_string)
{
    astFunc = p.parse_function("() 0");
    CHECK_EQUAL(std::string("() 0"), astFunc->get_string());
}

TEST(ParseFunction, Number)
{
    astFunc = p.parse_function("(a) 0");
    AstNumber *num = dynamic_cast<AstNumber *>(astFunc->body);
    CHECK(num);
}

TEST(ParseFunction, Identifier)
{
    astFunc = p.parse_function("(a) a");
    AstIdentifier *ident = dynamic_cast<AstIdentifier *>(astFunc->body);
    CHECK(ident);
}

TEST(ParseFunction, ArithExpression)
{
    astFunc = p.parse_function("(a) a + b");
    AstAddition *add = dynamic_cast<AstAddition *>(astFunc->body);
    CHECK(add);
}

TEST(ParseFunction, Assignment)
{
    astFunc = p.parse_function("(a) a = b");
    AstAssignment *assign = dynamic_cast<AstAssignment *>(astFunc->body);
    CHECK(assign);
}
TEST(ParseFunction, Compound)
{
    astFunc = p.parse_function("(a) {\na\nb\n}");
    AstCompound *com = dynamic_cast<AstCompound *>(astFunc->body);
    CHECK(com);
}
