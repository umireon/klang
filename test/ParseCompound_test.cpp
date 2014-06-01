#include <CppUTest/TestHarness.h>

#include <string>

#include "ast/AstNode.h"
#include "ast/AstCompound.h"
#include "ast/AstIdentifier.h"

#include "parser/ParseCompound.h"

TEST_GROUP(ParseCompound)
{
    ParseCompound p;
    AstNode *node;
    AstCompound *com;
    
    void teardown()
    {
        delete node;
    }
};

TEST(ParseCompound, get_string)
{
    std::string input("{x}");
    node = p.parse_compound(input.begin());
    CHECK_EQUAL(input, node->get_string());
}

TEST(ParseCompound, InLine)
{
    std::string input("{x}");
    node = p.parse_compound(input.begin());
    com = dynamic_cast<AstCompound *>(node);
    CHECK(com);
    
    AstIdentifier *ident = dynamic_cast<AstIdentifier *>(com->children.at(0));
	CHECK(ident);
	CHECK_EQUAL(std::string("x"), ident->get_string());
}

TEST(ParseCompound, SingleLine)
{
    std::string input("{\nx\n}");
    node = p.parse_compound(input.begin());
    com = dynamic_cast<AstCompound *>(node);
    CHECK(com);
    
    AstIdentifier *ident = dynamic_cast<AstIdentifier *>(com->children.at(0));
	CHECK(ident);
	CHECK_EQUAL(std::string("x"), ident->get_string());
}

TEST(ParseCompound, MultipleLine)
{
    std::string input("{\nx\ny\rz\n}");
    node = p.parse_compound(input.begin());
    com = dynamic_cast<AstCompound *>(node);
    CHECK(com);
    
    AstIdentifier *ident1 = dynamic_cast<AstIdentifier *>(com->children.at(0));
	CHECK(ident1);
	CHECK_EQUAL(std::string("x"), ident1->get_string());
    
    AstIdentifier *ident2 = dynamic_cast<AstIdentifier *>(com->children.at(1));
	CHECK(ident2);
	CHECK_EQUAL(std::string("y"), ident2->get_string());
    
    AstIdentifier *ident3 = dynamic_cast<AstIdentifier *>(com->children.at(2));
	CHECK(ident3);
	CHECK_EQUAL(std::string("z"), ident3->get_string());
}
