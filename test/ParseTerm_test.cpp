#include <iostream>
#include <CppUTest/TestHarness.h>

#include "../src/parser.h"

TEST_GROUP(ParseTerm)
{
};

TEST(ParseTerm, AstElement)
{
    ParseTerm p;
    AstNode *term = p.parse_term("0");
    CHECK(dynamic_cast<AstElement*>(term));

    delete term;
}

TEST(ParseTerm, 2ElemMultiplication)
{
    ParseTerm p;
    AstNode *term = p.parse_term("2*3");
    CHECK_EQUAL(2, term->size());
    CHECK_EQUAL(AST_MULTIPLICATION, term->type);

    std::vector<AstNode*> &children = term->children;
    CHECK_EQUAL(AST_ELEMENT, children[0]->type);
    CHECK_EQUAL(AST_ELEMENT, children[1]->type);

    delete term;
}

TEST(ParseTerm, 3ElemMultiplication)
{
    ParseTerm p;
    AstNode *term = p.parse_term("2*3*4");
    CHECK_EQUAL(2, term->size());
    CHECK_EQUAL(AST_MULTIPLICATION, term->type);

    std::vector<AstNode*> &children = term->children;
    CHECK_EQUAL(2, children[0]->size());
    CHECK_EQUAL(AST_MULTIPLICATION, children[0]->type);

    CHECK_EQUAL(AST_ELEMENT, children[0]->children[0]->type);
    CHECK_EQUAL(AST_ELEMENT, children[0]->children[1]->type);
    CHECK_EQUAL(AST_ELEMENT, children[1]->type);

    delete term;
}

TEST(ParseTerm, 2ElemDivision)
{
    ParseTerm p;
    AstNode *term = p.parse_term("2/3");
    CHECK_EQUAL(2, term->size());
    CHECK_EQUAL(AST_DIVISION, term->type);

    std::vector<AstNode*> &children = term->children;
    CHECK_EQUAL(AST_ELEMENT, children[0]->type);
    CHECK_EQUAL(AST_ELEMENT, children[1]->type);

    delete term;
}

TEST(ParseTerm, 3ElemDivision)
{
    ParseTerm p;
    AstNode *term = p.parse_term("2/3/4");
    CHECK_EQUAL(2, term->size());
    CHECK_EQUAL(AST_DIVISION, term->type);

    std::vector<AstNode*> &children = term->children;
    CHECK_EQUAL(2, children[0]->size());
    CHECK_EQUAL(AST_DIVISION, children[0]->type);

    CHECK_EQUAL(AST_ELEMENT, children[0]->children[0]->type);
    CHECK_EQUAL(AST_ELEMENT, children[0]->children[1]->type);
    CHECK_EQUAL(AST_ELEMENT, children[1]->type);

    delete term;
}

TEST(ParseTerm, 2ElemPower)
{
    ParseTerm p;
    AstNode *term = p.parse_term("2**3");
    CHECK_EQUAL(2, term->size());
    CHECK_EQUAL(AST_POWER, term->type);

    std::vector<AstNode*> &children = term->children;
    CHECK_EQUAL(AST_ELEMENT, children[0]->type);
    CHECK_EQUAL(AST_ELEMENT, children[1]->type);

    delete term;
}

TEST(ParseTerm, 3ElemPower)
{
    ParseTerm p;
    AstNode *term = p.parse_term("2**3**4");
    CHECK_EQUAL(2, term->size());
    CHECK_EQUAL(AST_POWER, term->type);

    std::vector<AstNode*> &children = term->children;
    CHECK_EQUAL(2, children[1]->size());
    CHECK_EQUAL(AST_POWER, children[1]->type);

    CHECK_EQUAL(AST_ELEMENT, children[0]->type);
    CHECK_EQUAL(AST_ELEMENT, children[1]->children[0]->type);
    CHECK_EQUAL(AST_ELEMENT, children[1]->children[1]->type);

    delete term;
}

TEST(ParseTerm, Complex)
{
    ParseTerm p;
    AstNode *term = p.parse_term("1*2**3*4");
    CHECK_EQUAL(2, term->size());
    CHECK_EQUAL(AST_MULTIPLICATION, term->type);

    std::vector<AstNode*> &children = term->children;
    CHECK_EQUAL(2, children[0]->size());
    CHECK_EQUAL(AST_MULTIPLICATION, children[0]->type);
    CHECK_EQUAL(2, children[0]->children[1]->size());
    CHECK_EQUAL(AST_POWER, children[0]->children[1]->type);

    CHECK_EQUAL(AST_ELEMENT, children[0]->children[0]->type);
    CHECK_EQUAL(AST_ELEMENT, children[0]->children[1]->children[0]->type);
    CHECK_EQUAL(AST_ELEMENT, children[0]->children[1]->children[1]->type);
    CHECK_EQUAL(AST_ELEMENT, children[1]->type);

    delete term;
}
