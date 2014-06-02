#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

#include <string>

#include "ast/AstNode.h"
#include "ast/AstDivision.h"
#include "ast/AstMultiplication.h"
#include "ast/AstNumber.h"
#include "ast/AstPower.h"
#include "ast/AstReminder.h"

#include "parser/BaseParse.h"
#include "parser/ParseTerm.h"

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
};

TEST_GROUP(ParseTerm)
{
    ParseNextMock *pn;
    ParseTerm *p;
    AstNode *node;
    
    void setup()
    {
        pn = new ParseNextMock();
        p = new ParseTerm();
        p->parseNext = pn;
    }
    
    void teardown()
    {
        delete p;
        delete pn;
        delete node;
        mock().clear();
    }
};

TEST(ParseTerm, get_string)
{
    std::string input("1");
    mock().expectOneCall("parse");
    node = p->parse_term(input.begin());
    CHECK_EQUAL(input, node->get_string());
}

TEST(ParseTerm, 2ElemMultiplication)
{
    std::string input("2*3");
    mock().expectNCalls(2, "parse");
    node = p->parse_term(input.begin());
    AstMultiplication *term = dynamic_cast<AstMultiplication *>(node);
    CHECK(term);
    std::vector<AstNode *> &children = term->children;
    
    CHECK_EQUAL(std::string("2"), children[0]->get_string());
    CHECK_EQUAL(std::string("3"), children[1]->get_string());
}

TEST(ParseTerm, 3ElemMultiplication)
{
    std::string input("2*3*4");
    mock().expectNCalls(3, "parse");
    node = p->parse_term(input.begin());
    AstMultiplication *term = dynamic_cast<AstMultiplication *>(node);
    CHECK(term);
    std::vector<AstNode *> &children = term->children;
    
    AstMultiplication *term0 = dynamic_cast<AstMultiplication *>(children[0]);
    CHECK(term0);
    std::vector<AstNode *> &children0 = term0->children;
    
    CHECK_EQUAL(std::string("2"), children0[0]->get_string());
    CHECK_EQUAL(std::string("3"), children0[1]->get_string());
    CHECK_EQUAL(std::string("4"), children[1]->get_string());
}

TEST(ParseTerm, 2ElemDivision)
{
    std::string input("2/3");
    mock().expectNCalls(2, "parse");
    node = p->parse_term(input.begin());
    AstDivision *term = dynamic_cast<AstDivision *>(node);
    CHECK(term);
    std::vector<AstNode *> &children = term->children;
    
    CHECK_EQUAL(std::string("2"), children[0]->get_string());
    CHECK_EQUAL(std::string("3"), children[1]->get_string());
}

TEST(ParseTerm, 3ElemDivision)
{
    std::string input("2/3/4");
    mock().expectNCalls(3, "parse");
    node = p->parse_term(input.begin());
    AstDivision *term = dynamic_cast<AstDivision *>(node);
    CHECK(term);
    std::vector<AstNode *> &children = term->children;
    
    AstDivision *term0 = dynamic_cast<AstDivision *>(children[0]);
    CHECK(term0);
    std::vector<AstNode *> &children0 = term0->children;
    
    CHECK_EQUAL(std::string("2"), children0[0]->get_string());
    CHECK_EQUAL(std::string("3"), children0[1]->get_string());
    CHECK_EQUAL(std::string("4"), children[1]->get_string());
}

TEST(ParseTerm, 2ElemReminder)
{
    std::string input("2%3");
    mock().expectNCalls(2, "parse");
    node = p->parse_term(input.begin());
    AstReminder *term = dynamic_cast<AstReminder *>(node);
    CHECK(term);
    std::vector<AstNode *> &children = term->children;
    
    CHECK_EQUAL(std::string("2"), children[0]->get_string());
    CHECK_EQUAL(std::string("3"), children[1]->get_string());
}

TEST(ParseTerm, 3ElemReminder)
{
    std::string input("2%3%4");
    mock().expectNCalls(3, "parse");
    node = p->parse_term(input.begin());
    AstReminder *term = dynamic_cast<AstReminder *>(node);
    CHECK(term);
    std::vector<AstNode *> &children = term->children;
    
    AstReminder *term0 = dynamic_cast<AstReminder *>(children[0]);
    CHECK(term0);
    std::vector<AstNode *> &children0 = term0->children;
    
    CHECK_EQUAL(std::string("2"), children0[0]->get_string());
    CHECK_EQUAL(std::string("3"), children0[1]->get_string());
    CHECK_EQUAL(std::string("4"), children[1]->get_string());
}

TEST(ParseTerm, 2ElemPower)
{
    std::string input("2**3");
    mock().expectNCalls(2, "parse");
    node = p->parse_term(input.begin());
    AstPower *term = dynamic_cast<AstPower *>(node);
    CHECK(term);
    std::vector<AstNode *> &children = term->children;
    
    CHECK_EQUAL(std::string("2"), children[0]->get_string());
    CHECK_EQUAL(std::string("3"), children[1]->get_string());
}

TEST(ParseTerm, 3ElemPower)
{
    std::string input("2**3**4");
    mock().expectNCalls(3, "parse");
    node = p->parse_term(input.begin());
    AstPower *term = dynamic_cast<AstPower *>(node);
    CHECK(term);
    std::vector<AstNode *> &children = term->children;
    
    AstPower *term1 = dynamic_cast<AstPower *>(children[1]);
    CHECK(term1);
    std::vector<AstNode *> &children1 = term1->children;
    
    CHECK_EQUAL(std::string("2"), children[0]->get_string());
    CHECK_EQUAL(std::string("3"), children1[0]->get_string());
    CHECK_EQUAL(std::string("4"), children1[1]->get_string());
}

TEST(ParseTerm, 4ElemPower)
{
    std::string input("2**3**4**5");
    mock().expectNCalls(4, "parse");
    node = p->parse_term(input.begin());
    AstPower *term = dynamic_cast<AstPower *>(node);
    CHECK(term);
    std::vector<AstNode *> &children = term->children;
    
    AstPower *term1 = dynamic_cast<AstPower *>(children[1]);
    CHECK(term1);
    std::vector<AstNode *> &children1 = term1->children;
    
    AstPower *term11 = dynamic_cast<AstPower *>(children1[1]);
    CHECK(term11);
    std::vector<AstNode *> &children11 = term11->children;
    
    CHECK_EQUAL(std::string("2"), children[0]->get_string());
    CHECK_EQUAL(std::string("3"), children1[0]->get_string());
    CHECK_EQUAL(std::string("4"), children11[0]->get_string());
    CHECK_EQUAL(std::string("5"), children11[1]->get_string());
}

TEST(ParseTerm, Complex)
{
    std::string input("1*2**3/4%5");
    mock().expectNCalls(5, "parse");
    node = p->parse_term(input.begin());
    AstReminder *term = dynamic_cast<AstReminder *>(node);
    CHECK(term);
    std::vector<AstNode *> &children = term->children;
    
    AstDivision *term0 = dynamic_cast<AstDivision *>(children[0]);
    CHECK(term0);
    std::vector<AstNode *> &children0 = term0->children;
    
    AstMultiplication *term00 = dynamic_cast<AstMultiplication *>(children0[0]);
    CHECK(term00);
    std::vector<AstNode *> &children00 = term00->children;
    
    AstPower *term001 = dynamic_cast<AstPower *>(children00[1]);
    CHECK(term001);
    std::vector<AstNode *> &children001 = term001->children;
    
    CHECK_EQUAL(std::string("1"), children00[0]->get_string());
    CHECK_EQUAL(std::string("2"), children001[0]->get_string());
    CHECK_EQUAL(std::string("3"), children001[1]->get_string());
    CHECK_EQUAL(std::string("4"), children0[1]->get_string());
    CHECK_EQUAL(std::string("5"), children[1]->get_string());
}

TEST(ParseTerm, Whitespace)
{
    std::string input("1  *   2   **   3   /  4  %   5");
    mock().expectNCalls(5, "parse");
    node = p->parse_term(input.begin());
    AstReminder *term = dynamic_cast<AstReminder *>(node);
    CHECK(term);
    std::vector<AstNode *> &children = term->children;
    
    AstDivision *term0 = dynamic_cast<AstDivision *>(children[0]);
    CHECK(term0);
    std::vector<AstNode *> &children0 = term0->children;
    
    AstMultiplication *term00 = dynamic_cast<AstMultiplication *>(children0[0]);
    CHECK(term00);
    std::vector<AstNode *> &children00 = term00->children;
    
    AstPower *term001 = dynamic_cast<AstPower *>(children00[1]);
    CHECK(term001);
    std::vector<AstNode *> &children001 = term001->children;
    
    CHECK_EQUAL(std::string("1"), children00[0]->get_string());
    CHECK_EQUAL(std::string("2"), children001[0]->get_string());
    CHECK_EQUAL(std::string("3"), children001[1]->get_string());
    CHECK_EQUAL(std::string("4"), children0[1]->get_string());
    CHECK_EQUAL(std::string("5"), children[1]->get_string());
}
