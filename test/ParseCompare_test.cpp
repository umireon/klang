#include <CppUTest/TestHarness.h>

#include <stdexcept>
#include <string>
#include <memory>

#include "ast/AstNumber.h"
#include "ast/AstAddition.h"
#include "ast/AstSubtraction.h"

#include "parser/ParseCompare.h"

TEST_GROUP(ParseCompare)
{
    ParseCompare p;
    AstNode *node;
    
    void teardown()
    {
        delete node;
    }
};

TEST(ParseCompare, GreaterThan)
{
    std::string input("1>2");
    node = p.parse_compare(input.begin());
    AstGreaterThan *cmp = dynamic_cast<AstGreaterThan *>(node);
    CHECK(cmp);
    CHECK_EQUAL(input, cmp->get_string());
    
    CHECK_EQUAL(2, cmp->size());
    CHECK_EQUAL("1", cmp->children[0]->get_string());
    CHECK_EQUAL("2", cmp->children[1]->get_string());
}

TEST(ParseCompare, GreaterThanEqual)
{
    std::string input("1>=2");
    node = p.parse_compare(input.begin());
    AstGreaterThanEqual *cmp = dynamic_cast<AstGreaterThanEqual *>(node);
    CHECK(cmp);
    CHECK_EQUAL(input, cmp->get_string());
    
    CHECK_EQUAL(2, cmp->size());
    CHECK_EQUAL("1", cmp->children[0]->get_string());
    CHECK_EQUAL("2", cmp->children[1]->get_string());
}

TEST(ParseCompare, GreaterThanWhitespace)
{
    std::string input("1  >  2");
    node = p.parse_compare(input.begin());
    AstGreaterThan *cmp = dynamic_cast<AstGreaterThan *>(node);
    CHECK(cmp);
    CHECK_EQUAL(input, cmp->get_string());
    
    CHECK_EQUAL(2, cmp->size());
    CHECK_EQUAL("1", cmp->children[0]->get_string());
    CHECK_EQUAL("2", cmp->children[1]->get_string());
}

TEST(ParseCompare, LessThan)
{
    std::string input("1<2");
    node = p.parse_compare(input.begin());
    AstLessThan *cmp = dynamic_cast<AstLessThan *>(node);
    CHECK(cmp);
    CHECK_EQUAL(input, cmp->get_string());
    
    CHECK_EQUAL(2, cmp->size());
    CHECK_EQUAL("1", cmp->children[0]->get_string());
    CHECK_EQUAL("2", cmp->children[1]->get_string());
}

TEST(ParseCompare, LessThanEqual)
{
    std::string input("1<=2");
    node = p.parse_compare(input.begin());
    AstLessThanEqual *cmp = dynamic_cast<AstLessThanEqual *>(node);
    CHECK(cmp);
    CHECK_EQUAL(input, cmp->get_string());
    
    CHECK_EQUAL(2, cmp->size());
    CHECK_EQUAL("1", cmp->children[0]->get_string());
    CHECK_EQUAL("2", cmp->children[1]->get_string());
}

TEST(ParseCompare, LessThanWhitespace)
{
    std::string input("1  <  2");
    node = p.parse_compare(input.begin());
    AstLessThan *cmp = dynamic_cast<AstLessThan *>(node);
    CHECK(cmp);
    CHECK_EQUAL(input, cmp->get_string());
    
    CHECK_EQUAL(2, cmp->size());
    CHECK_EQUAL("1", cmp->children[0]->get_string());
    CHECK_EQUAL("2", cmp->children[1]->get_string());
}
