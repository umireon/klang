#include <iostream>
#include <CppUTest/TestHarness.h>

#include "../src/Parse.h"

using std::string;

TEST_GROUP(ParseArithExpression)
{
    Binding *b;
    void setup()
    {
        b = new Binding();
    }
    
    void teardown()
    {
        delete b;
    }
};

TEST(ParseArithExpression, AstNumber)
{
    ParseArithExpression p;
    AstNode *expr = p.parse_arith_expression("0");
    CHECK(dynamic_cast<AstNumber*>(expr));
    
    delete expr;
}

TEST(ParseArithExpression, 2ElemAddition)
{
    ParseArithExpression p;
    
    AstAddition *expr = dynamic_cast<AstAddition*>(p.parse_arith_expression("2+3"));
    CHECK(expr);
    std::vector<AstNode*> &children = expr->children;
    
    CHECK_EQUAL(string("2"), children[0]->get_string());
    CHECK_EQUAL(string("3"), children[1]->get_string());
    
    delete expr;
}

TEST(ParseArithExpression, 3ElemAddition)
{
    ParseArithExpression p;
    
    AstAddition *expr = dynamic_cast<AstAddition*>(p.parse_arith_expression("2+3+4"));
    CHECK(expr);
    std::vector<AstNode*> &children = expr->children;
    
    AstAddition *expr0 = dynamic_cast<AstAddition*>(children[0]);
    CHECK(expr0);
    std::vector<AstNode*> &children0 = expr0->children;
    
    CHECK_EQUAL(string("2"), children0[0]->get_string());
    CHECK_EQUAL(string("3"), children0[1]->get_string());
    CHECK_EQUAL(string("4"), children[1]->get_string());
    
    delete expr;
}

TEST(ParseArithExpression, 2ElemSubtraction)
{
    ParseArithExpression p;
    
    AstSubtraction *expr = dynamic_cast<AstSubtraction*>(p.parse_arith_expression("2-3"));
    CHECK(expr);
    std::vector<AstNode*> &children = expr->children;
    
    CHECK_EQUAL(string("2"), children[0]->get_string());
    CHECK_EQUAL(string("3"), children[1]->get_string());
    
    delete expr;
}

TEST(ParseArithExpression, 3ElemSubtraction)
{
    ParseArithExpression p;
    
    AstSubtraction *expr = dynamic_cast<AstSubtraction*>(p.parse_arith_expression("2-3-4"));
    CHECK(expr);
    std::vector<AstNode*> &children = expr->children;
    
    AstSubtraction *expr0 = dynamic_cast<AstSubtraction*>(children[0]);
    CHECK(expr0);
    std::vector<AstNode*> &children0 = expr0->children;
    
    CHECK_EQUAL(string("2"), children0[0]->get_string());
    CHECK_EQUAL(string("3"), children0[1]->get_string());
    CHECK_EQUAL(string("4"), children[1]->get_string());
    
    delete expr;
}

TEST(ParseArithExpression, Complex)
{
    ParseArithExpression p;
    
    AstSubtraction *expr = dynamic_cast<AstSubtraction*>(p.parse_arith_expression("2+3-4"));
    CHECK(expr);
    std::vector<AstNode*> &children = expr->children;
    
    AstAddition *expr0 = dynamic_cast<AstAddition*>(children[0]);
    CHECK(expr0);
    std::vector<AstNode*> &children0 = expr0->children;
    
    CHECK_EQUAL(string("2"), children0[0]->get_string());
    CHECK_EQUAL(string("3"), children0[1]->get_string());
    CHECK_EQUAL(string("4"), children[1]->get_string());
    
    delete expr;
}

TEST(ParseArithExpression, Whitespace)
{
    ParseArithExpression p;
    
    AstSubtraction *expr = dynamic_cast<AstSubtraction*>(p.parse_arith_expression("2 + 3 - 4"));
    CHECK(expr);
    std::vector<AstNode*> &children = expr->children;
    
    AstAddition *expr0 = dynamic_cast<AstAddition*>(children[0]);
    CHECK(expr0);
    std::vector<AstNode*> &children0 = expr0->children;
    
    CHECK_EQUAL(string("2"), children0[0]->get_string());
    CHECK_EQUAL(string("3"), children0[1]->get_string());
    CHECK_EQUAL(string("4"), children[1]->get_string());
    
    delete expr;
}

