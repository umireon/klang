#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

#include <string>

#include "ast/AstAssignment.h"

#include "parser/types.h"
#include "parser/BaseParse.h"
#include "parser/ParseAssignment.h"

TEST_GROUP(ParseAssignment)
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

    ParseAssignment parseAssignment, *p;

    AstNode *node;
    
    void setup()
    {
        p = &parseAssignment;
        p->parseNext = &parseNextMock;
    }
    
    void teardown()
    {
        delete node;
        mock().clear();
    }
};

TEST(ParseAssignment, get_string)
{
    std::string input("a=3");
    mock().expectNCalls(2, "parse");
    node = p->parse_assignment(input.begin());
    CHECK_EQUAL(input, node->get_string());
}

TEST(ParseAssignment, 2ExpressionAssignment)
{
    std::string input("a=3");
    mock().expectNCalls(2, "parse");
    node = p->parse_assignment(input.begin());
    AstAssignment *assign = dynamic_cast<AstAssignment *>(node);
    CHECK(assign);
    std::vector<AstNode *> &children = assign->children;
    
    CHECK_EQUAL(std::string("a"), children[0]->get_string());
    CHECK_EQUAL(std::string("3"), children[1]->get_string());
}

TEST(ParseAssignment, 3ExpressionAssignment)
{
    std::string input("a=b=4");
    mock().expectNCalls(3, "parse");
    node = p->parse_assignment(input.begin());
    AstAssignment *assign = dynamic_cast<AstAssignment *>(node);
    CHECK(assign);
    std::vector<AstNode *> &children = assign->children;
    
    AstAssignment *assign1 = dynamic_cast<AstAssignment *>(children[1]);
    CHECK(assign1);
    std::vector<AstNode *> &children1 = assign1->children;
    
    CHECK_EQUAL(std::string("a"), children[0]->get_string());
    CHECK_EQUAL(std::string("b"), children1[0]->get_string());
    CHECK_EQUAL(std::string("4"), children1[1]->get_string());
}

TEST(ParseAssignment, Whitespace)
{
    std::string input("a =  b  =  4");
    mock().expectNCalls(3, "parse");
    node = p->parse_assignment(input.begin());
    AstAssignment *assign = dynamic_cast<AstAssignment *>(node);
    CHECK(assign);
    std::vector<AstNode *> &children = assign->children;
    
    AstAssignment *assign1 = dynamic_cast<AstAssignment *>(children[1]);
    CHECK(assign1);
    std::vector<AstNode *> &children1 = assign1->children;
    
    CHECK_EQUAL(std::string("a"), children[0]->get_string());
    CHECK_EQUAL(std::string("b"), children1[0]->get_string());
    CHECK_EQUAL(std::string("4"), children1[1]->get_string());
}
