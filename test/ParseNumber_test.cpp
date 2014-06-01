#include <CppUTest/TestHarness.h>
#include <cfloat>
#include <limits.h>

#include "parser.h"

TEST_GROUP(ParseNumber)
{
    ParseNumber p;
    AstNumber *num;
    
    void teardown()
    {
        delete num;
    }
};

TEST(ParseNumber, get_string)
{
    std::string input("2");
    num = p.parse_number(input.begin());
    CHECK_EQUAL(input, num->get_string());
}

TEST(ParseNumber, NoChildren)
{
    std::string input("2");
    num = p.parse_number(input.begin());
    CHECK_EQUAL(0, num->size());
}
