#include <iostream>
#include <CppUTest/TestHarness.h>

#include "../src/parser.h"

TEST_GROUP(ParseExpression)
{
};

TEST(ParseExpression, AstElement)
{
    ParseExpression p;
    AstNode *expr = p.parse_expression("0");
    CHECK(dynamic_cast<AstElement*>(expr));

    delete expr;
}

TEST(ParseExpression, 2ElemAddition)
{
    ParseExpression p;
    AstNode *expr = p.parse_expression("2+3");
    CHECK_EQUAL(2, expr->size());
    CHECK_EQUAL(AST_ADDITION, expr->type);

    std::vector<AstNode*> &children = expr->children;
    CHECK_EQUAL(AST_ELEMENT, children[0]->type);
    CHECK_EQUAL(AST_ELEMENT, children[1]->type);

    delete expr;
}

TEST(ParseExpression, 3ElemAddition)
{
    ParseExpression p;
    AstNode *expr = p.parse_expression("2+3+4");
    CHECK_EQUAL(2, expr->size());
    CHECK_EQUAL(AST_ADDITION, expr->type);

    std::vector<AstNode*> &children = expr->children;
    CHECK_EQUAL(2, children[0]->size());
    CHECK_EQUAL(AST_ADDITION, children[0]->type);

    CHECK_EQUAL(AST_ELEMENT, children[0]->children[0]->type);
    CHECK_EQUAL(AST_ELEMENT, children[0]->children[1]->type);
    CHECK_EQUAL(AST_ELEMENT, children[1]->type);

    delete expr;
}

TEST(ParseExpression, 2ElemSubtraction)
{
    ParseExpression p;
    AstNode *expr = p.parse_expression("2-3");
    CHECK_EQUAL(2, expr->size());
    CHECK_EQUAL(AST_SUBTRACTION, expr->type);

    std::vector<AstNode*> &children = expr->children;
    CHECK_EQUAL(AST_ELEMENT, children[0]->type);
    CHECK_EQUAL(AST_ELEMENT, children[1]->type);

    delete expr;
}

TEST(ParseExpression, 3ElemSubtraction)
{
    ParseExpression p;
    AstNode *expr = p.parse_expression("2-3-4");
    CHECK_EQUAL(2, expr->size());
    CHECK_EQUAL(AST_SUBTRACTION, expr->type);

    std::vector<AstNode*> &children = expr->children;
    CHECK_EQUAL(2, children[0]->size());
    CHECK_EQUAL(AST_SUBTRACTION, children[0]->type);

    CHECK_EQUAL(AST_ELEMENT, children[0]->children[0]->type);
    CHECK_EQUAL(AST_ELEMENT, children[0]->children[1]->type);
    CHECK_EQUAL(AST_ELEMENT, children[1]->type);

    delete expr;
}
