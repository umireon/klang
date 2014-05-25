#include <iostream>
#include <CppUTest/TestHarness.h>

#include "../src/Parse.h"

TEST_GROUP(ParseTerm)
{
};

TEST(ParseTerm, AstElement)
{
    ParseTerm p;
    AstNode *term = p.parse_term("0");
    CHECK(dynamic_cast<AstNumber*>(term));

    delete term;
}

TEST(ParseTerm, 2ElemMultiplication)
{
    ParseTerm p;
    AstNode *term = p.parse_term("2*3");
    CHECK_EQUAL(2, term->size());
    CHECK(dynamic_cast<AstMultiplication*>(term));

    std::vector<AstNode*> &children = term->children;
    CHECK_EQUAL(2, children[0]->get_long());
    CHECK_EQUAL(3, children[1]->get_long());

    delete term;
}

TEST(ParseTerm, 3ElemMultiplication)
{
    ParseTerm p;
    AstNode *term = p.parse_term("2*3*4");
    CHECK_EQUAL(2, term->size());
    CHECK(dynamic_cast<AstMultiplication*>(term));

    std::vector<AstNode*> &children = term->children;
    CHECK_EQUAL(2, children[0]->size());
    CHECK(dynamic_cast<AstMultiplication*>(children[0]));

    CHECK_EQUAL(2, children[0]->children[0]->get_long());
    CHECK_EQUAL(3, children[0]->children[1]->get_long());
    CHECK_EQUAL(4, children[1]->get_long());

    delete term;
}

TEST(ParseTerm, 2ElemDivision)
{
    ParseTerm p;
    AstNode *term = p.parse_term("2/3");
    CHECK_EQUAL(2, term->size());
    CHECK(dynamic_cast<AstDivision*>(term));

    std::vector<AstNode*> &children = term->children;
    CHECK_EQUAL(2, children[0]->get_long());
    CHECK_EQUAL(3, children[1]->get_long());

    delete term;
}

TEST(ParseTerm, 3ElemDivision)
{
    ParseTerm p;
    AstNode *term = p.parse_term("2/3/4");
    CHECK_EQUAL(2, term->size());
    CHECK(dynamic_cast<AstDivision*>(term));

    std::vector<AstNode*> &children = term->children;
    CHECK_EQUAL(2, children[0]->size());
    CHECK(dynamic_cast<AstDivision*>(children[0]));

    CHECK_EQUAL(2, children[0]->children[0]->get_long());
    CHECK_EQUAL(3, children[0]->children[1]->get_long());
    CHECK_EQUAL(4, children[1]->get_long());

    delete term;
}

TEST(ParseTerm, 2ElemReminder)
{
    ParseTerm p;
    AstNode *term = p.parse_term("2%3");
    CHECK_EQUAL(2, term->size());
    CHECK(dynamic_cast<AstReminder*>(term));

    std::vector<AstNode*> &children = term->children;
    CHECK_EQUAL(2, children[0]->get_long());
    CHECK_EQUAL(3, children[1]->get_long());

    delete term;
}

TEST(ParseTerm, 3ElemReminder)
{
    ParseTerm p;
    AstNode *term = p.parse_term("2%3%4");
    CHECK_EQUAL(2, term->size());
    CHECK(dynamic_cast<AstReminder*>(term));

    std::vector<AstNode*> &children = term->children;
    CHECK_EQUAL(2, children[0]->size());
    CHECK(dynamic_cast<AstReminder*>(children[0]));

    CHECK_EQUAL(2, children[0]->children[0]->get_long());
    CHECK_EQUAL(3, children[0]->children[1]->get_long());
    CHECK_EQUAL(4, children[1]->get_long());

    delete term;
}

TEST(ParseTerm, 2ElemPower)
{
    ParseTerm p;
    AstNode *term = p.parse_term("2**3");
    CHECK_EQUAL(2, term->size());
    CHECK(dynamic_cast<AstPower*>(term));

    std::vector<AstNode*> &children = term->children;
    CHECK_EQUAL(2, children[0]->get_long());
    CHECK_EQUAL(3, children[1]->get_long());

    delete term;
}

TEST(ParseTerm, 3ElemPower)
{
    ParseTerm p;
    AstNode *term = p.parse_term("2**3**4");
    CHECK_EQUAL(2, term->size());
    CHECK(dynamic_cast<AstPower*>(term));

    std::vector<AstNode*> &children = term->children;
    CHECK_EQUAL(2, children[1]->size());
    CHECK(dynamic_cast<AstPower*>(children[1]));

    CHECK_EQUAL(2, children[0]->get_long());
    CHECK_EQUAL(3, children[1]->children[0]->get_long());
    CHECK_EQUAL(4, children[1]->children[1]->get_long());

    delete term;
}

TEST(ParseTerm, Complex)
{
    ParseTerm p;
    AstNode *term = p.parse_term("1*2**3/4");
    CHECK_EQUAL(2, term->size());
    CHECK(dynamic_cast<AstDivision*>(term));

    std::vector<AstNode*> &children = term->children;
    CHECK_EQUAL(2, children[0]->size());
    CHECK(dynamic_cast<AstMultiplication*>(children[0]));
    CHECK_EQUAL(2, children[0]->children[1]->size());
    CHECK(dynamic_cast<AstPower*>(children[0]->children[1]));

    CHECK_EQUAL(1, children[0]->children[0]->get_long());
    CHECK_EQUAL(2, children[0]->children[1]->children[0]->get_long());
    CHECK_EQUAL(3, children[0]->children[1]->children[1]->get_long());
    CHECK_EQUAL(4, children[1]->get_long());

    delete term;
}
