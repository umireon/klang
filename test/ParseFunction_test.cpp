#include <CppUTest/TestHarness.h>

#include <string>

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
    std::string input("() 0");
    astFunc = p.parse_function(input.begin());
    CHECK_EQUAL(input, astFunc->get_string());
}

TEST(ParseFunction, Number)
{
    std::string input("(a) 0");
    astFunc = p.parse_function(input.begin());
    AstNumber *num = dynamic_cast<AstNumber *>(astFunc->body);
    CHECK(num);
}

TEST(ParseFunction, Identifier)
{
    std::string input("(a) a");
    astFunc = p.parse_function(input.begin());
    AstIdentifier *ident = dynamic_cast<AstIdentifier *>(astFunc->body);
    CHECK(ident);
}

TEST(ParseFunction, ArithExpression)
{
    std::string input("(a) a + b");
    astFunc = p.parse_function(input.begin());
    AstAddition *add = dynamic_cast<AstAddition *>(astFunc->body);
    CHECK(add);
}

TEST(ParseFunction, Assignment)
{
    std::string input("(a) a = b");
    astFunc = p.parse_function(input.begin());
    AstAssignment *assign = dynamic_cast<AstAssignment *>(astFunc->body);
    CHECK(assign);
}
TEST(ParseFunction, Compound)
{
    std::string input("(a) {\na\nb\n}");
    astFunc = p.parse_function(input.begin());
    AstCompound *com = dynamic_cast<AstCompound *>(astFunc->body);
    CHECK(com);
}
