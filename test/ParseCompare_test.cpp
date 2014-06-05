#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

#include <string>

#include "ast/AstNode.h"

#include "parser/types.h"
#include "parser/BaseParse.h"
#include "parser/ParseCompare.h"

TEST_GROUP(ParseCompare)
{
    class ParseNextMock : public BaseParse
    {
        virtual AstNode *parse(pstr_t str)
        {
            mock().actualCall("parse");
            AstNode *node = new AstNode();
            node->strhead = str;
            node->strtail = str + 1;
            return node;
        }
    } parseNextMock;

    ParseCompare parseCompare, *p;
    SyntaxErrorHandler seh;

    AstNode *node;
    
    void setup()
    {
        p = &parseCompare;
        p->parseNext = &parseNextMock;
    }
    
    void teardown()
    {
        delete node;
        mock().clear();
    }
};

TEST(ParseCompare, GreaterThan)
{
    std::string input("1>2");
    mock().expectNCalls(2, "parse");
    seh.line = &input;
    p->line = &input;
    p->syntaxErrorHandler = &seh;
    node = p->parse_compare(input.begin());
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
    mock().expectNCalls(2, "parse");
    seh.line = &input;
    p->line = &input;
    p->syntaxErrorHandler = &seh;
    node = p->parse_compare(input.begin());
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
    mock().expectNCalls(2, "parse");
    seh.line = &input;
    p->line = &input;
    p->syntaxErrorHandler = &seh;
    node = p->parse_compare(input.begin());
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
    mock().expectNCalls(2, "parse");
    seh.line = &input;
    p->line = &input;
    p->syntaxErrorHandler = &seh;
    node = p->parse_compare(input.begin());
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
    mock().expectNCalls(2, "parse");
    seh.line = &input;
    p->line = &input;
    p->syntaxErrorHandler = &seh;
    node = p->parse_compare(input.begin());
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
    mock().expectNCalls(2, "parse");
    seh.line = &input;
    p->line = &input;
    p->syntaxErrorHandler = &seh;
    node = p->parse_compare(input.begin());
    AstLessThan *cmp = dynamic_cast<AstLessThan *>(node);
    CHECK(cmp);
    CHECK_EQUAL(input, cmp->get_string());
    
    CHECK_EQUAL(2, cmp->size());
    CHECK_EQUAL("1", cmp->children[0]->get_string());
    CHECK_EQUAL("2", cmp->children[1]->get_string());
}
