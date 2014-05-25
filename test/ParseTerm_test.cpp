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

    AstMultiplication *term = dynamic_cast<AstMultiplication*>(p.parse_term("2*3"));
    CHECK(term);
    std::vector<AstNode*> &children = term->children;

    CHECK_EQUAL(2, children[0]->get_long());
    CHECK_EQUAL(3, children[1]->get_long());

    delete term;
}

TEST(ParseTerm, 3ElemMultiplication)
{
    ParseTerm p;

    AstMultiplication *term = dynamic_cast<AstMultiplication*>(p.parse_term("2*3*4"));
    CHECK(term);
    std::vector<AstNode*> &children = term->children;
    
    AstMultiplication *term0 = dynamic_cast<AstMultiplication*>(children[0]);
    CHECK(term0);
    std::vector<AstNode*> &children0 = term0->children;

    CHECK_EQUAL(2, children0[0]->get_long());
    CHECK_EQUAL(3, children0[1]->get_long());
    CHECK_EQUAL(4, children[1]->get_long());

    delete term;
}

TEST(ParseTerm, 2ElemDivision)
{
    ParseTerm p;

    AstDivision *term = dynamic_cast<AstDivision*>(p.parse_term("2/3"));
    CHECK(term);
    std::vector<AstNode*> &children = term->children;

    CHECK_EQUAL(2, children[0]->get_long());
    CHECK_EQUAL(3, children[1]->get_long());

    delete term;
}

TEST(ParseTerm, 3ElemDivision)
{
    ParseTerm p;

    AstDivision *term = dynamic_cast<AstDivision*>(p.parse_term("2/3/4"));
    CHECK(term);
    std::vector<AstNode*> &children = term->children;
    
    AstDivision *term0 = dynamic_cast<AstDivision*>(children[0]);
    CHECK(term0);
    std::vector<AstNode*> &children0 = term0->children;
    
    CHECK_EQUAL(2, children0[0]->get_long());
    CHECK_EQUAL(3, children0[1]->get_long());
    CHECK_EQUAL(4, children[1]->get_long());
    
    delete term;
}

TEST(ParseTerm, 2ElemReminder)
{
    ParseTerm p;

    AstReminder *term = dynamic_cast<AstReminder*>(p.parse_term("2%3"));
    CHECK(term);
    std::vector<AstNode*> &children = term->children;

    CHECK_EQUAL(2, children[0]->get_long());
    CHECK_EQUAL(3, children[1]->get_long());

    delete term;
}

TEST(ParseTerm, 3ElemReminder)
{
    ParseTerm p;

    AstReminder *term = dynamic_cast<AstReminder*>(p.parse_term("2%3%4"));
    CHECK(term);
    std::vector<AstNode*> &children = term->children;
    
    AstReminder *term0 = dynamic_cast<AstReminder*>(children[0]);
    CHECK(term0);
    std::vector<AstNode*> &children0 = term0->children;
    
    CHECK_EQUAL(2, children0[0]->get_long());
    CHECK_EQUAL(3, children0[1]->get_long());
    CHECK_EQUAL(4, children[1]->get_long());
    
    delete term;
}

TEST(ParseTerm, 2ElemPower)
{
    ParseTerm p;

    AstPower *term = dynamic_cast<AstPower*>(p.parse_term("2**3"));
    CHECK(term);
    std::vector<AstNode*> &children = term->children;

    CHECK_EQUAL(2, children[0]->get_long());
    CHECK_EQUAL(3, children[1]->get_long());

    delete term;
}

TEST(ParseTerm, 3ElemPower)
{
    ParseTerm p;

    AstPower *term = dynamic_cast<AstPower*>(p.parse_term("2**3**4"));
    CHECK(term);
    std::vector<AstNode*> &children = term->children;
    
    AstPower *term1 = dynamic_cast<AstPower*>(children[1]);
    CHECK(term1);
    std::vector<AstNode*> &children1 = term1->children;

    CHECK_EQUAL(2, children[0]->get_long());
    CHECK_EQUAL(3, children1[0]->get_long());
    CHECK_EQUAL(4, children1[1]->get_long());

    delete term;
}

TEST(ParseTerm, Complex)
{
    ParseTerm p;

    AstReminder *term = dynamic_cast<AstReminder*>(p.parse_term("1*2**3/4%5"));
    CHECK(term);
    std::vector<AstNode*> &children = term->children;

    AstDivision *term0 = dynamic_cast<AstDivision*>(children[0]);
    CHECK(term0);
    std::vector<AstNode*> &children0 = term0->children;

    AstMultiplication *term00 = dynamic_cast<AstMultiplication*>(children0[0]);
    CHECK(term00);
    std::vector<AstNode*> &children00 = term00->children;
    
    AstPower *term001 = dynamic_cast<AstPower*>(children00[1]);
    CHECK(term001);
    std::vector<AstNode*> &children001 = term001->children;

    CHECK_EQUAL(1, children00[0]->get_long());
    CHECK_EQUAL(2, children001[0]->get_long());
    CHECK_EQUAL(3, children001[1]->get_long());
    CHECK_EQUAL(4, children0[1]->get_long());
    CHECK_EQUAL(5, children[1]->get_long());

    delete term;
}

TEST(ParseTerm, Whitespace)
{
    ParseTerm p;

    AstReminder *term = dynamic_cast<AstReminder*>(p.parse_term("1 * 2 ** 3 / 4 % 5"));
    CHECK(term);
    std::vector<AstNode*> &children = term->children;

    AstDivision *term0 = dynamic_cast<AstDivision*>(children[0]);
    CHECK(term0);
    std::vector<AstNode*> &children0 = term0->children;

    AstMultiplication *term00 = dynamic_cast<AstMultiplication*>(children0[0]);
    CHECK(term00);
    std::vector<AstNode*> &children00 = term00->children;
    
    AstPower *term001 = dynamic_cast<AstPower*>(children00[1]);
    CHECK(term001);
    std::vector<AstNode*> &children001 = term001->children;

    CHECK_EQUAL(1, children00[0]->get_long());
    CHECK_EQUAL(2, children001[0]->get_long());
    CHECK_EQUAL(3, children001[1]->get_long());
    CHECK_EQUAL(4, children0[1]->get_long());
    CHECK_EQUAL(5, children[1]->get_long());

    delete term;
}
