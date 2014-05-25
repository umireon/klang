#include <iostream>
#include <CppUTest/TestHarness.h>

#include "../src/parser.h"

TEST_GROUP(ParseExpression)
{
};

TEST(ParseExpression, AstNumber)
{
    ParseExpression p;
    AstNode *expr = p.parse_expression("0");
    CHECK(dynamic_cast<AstNumber*>(expr));

    delete expr;
}

TEST(ParseExpression, 2ElemAddition)
{
    ParseExpression p;
    AstNode *expr = p.parse_expression("2+3");
    CHECK_EQUAL(2, expr->size());
    CHECK(dynamic_cast<AstAddition*>(expr));

    std::vector<AstNode*> &children = expr->children;
    CHECK_EQUAL(2, children[0]->get_long());
    CHECK_EQUAL(3, children[1]->get_long());

    delete expr;
}

TEST(ParseExpression, 3ElemAddition)
{
    ParseExpression p;
    AstNode *expr = p.parse_expression("2+3+4");
    CHECK_EQUAL(2, expr->size());
    CHECK(dynamic_cast<AstAddition*>(expr));

    std::vector<AstNode*> &children = expr->children;
    CHECK_EQUAL(2, children[0]->size());
    CHECK(dynamic_cast<AstAddition*>(children[0]));

    CHECK_EQUAL(2, children[0]->children[0]->get_long());
    CHECK_EQUAL(3, children[0]->children[1]->get_long());
    CHECK_EQUAL(4, children[1]->get_long());

    delete expr;
}

TEST(ParseExpression, 2ElemSubtraction)
{
    ParseExpression p;
    AstNode *expr = p.parse_expression("2-3");
    CHECK_EQUAL(2, expr->size());
    CHECK(dynamic_cast<AstSubtraction*>(expr));

    std::vector<AstNode*> &children = expr->children;
    CHECK_EQUAL(2, children[0]->get_long());
    CHECK_EQUAL(3, children[1]->get_long());

    delete expr;
}

TEST(ParseExpression, 3ElemSubtraction)
{
    ParseExpression p;
    AstNode *expr = p.parse_expression("2-3-4");
    CHECK_EQUAL(2, expr->size());
    CHECK(dynamic_cast<AstSubtraction*>(expr));

    std::vector<AstNode*> &children = expr->children;
    CHECK_EQUAL(2, children[0]->size());
    CHECK(dynamic_cast<AstSubtraction*>(children[0]));

    CHECK_EQUAL(2, children[0]->children[0]->get_long());
    CHECK_EQUAL(3, children[0]->children[1]->get_long());
    CHECK_EQUAL(4, children[1]->get_long());

    delete expr;
}
