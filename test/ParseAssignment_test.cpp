#include <iostream>
#include <string>
#include <CppUTest/TestHarness.h>

#include "../src/Parse.h"

TEST_GROUP(ParseAssignment)
{
};

TEST(ParseAssignment, 2ExpressionAssignment)
{
    ParseAssignment p;

    AstAssignment *assign = dynamic_cast<AstAssignment*>(p.parse_assignment("a=3"));
    CHECK(assign);
    std::vector<AstNode*> &children = assign->children;

    CHECK_EQUAL(std::string("a"), children[0]->get_string());
    CHECK_EQUAL(3, children[1]->get_long());

    delete assign;
}

TEST(ParseAssignment, 3ExpressionAssignment)
{
    ParseAssignment p;

    AstAssignment *assign = dynamic_cast<AstAssignment*>(p.parse_assignment("a=b=4"));
    CHECK(assign);
    std::vector<AstNode*> &children = assign->children;
    
    AstAssignment *assign1 = dynamic_cast<AstAssignment*>(children[1]);
    CHECK(assign1);
    std::vector<AstNode*> &children1 = assign1->children;

    CHECK_EQUAL(std::string("a"), children[0]->get_string());
    CHECK_EQUAL(std::string("b"), children1[0]->get_string());
    CHECK_EQUAL(4, children1[1]->get_long());

    delete assign;
}
