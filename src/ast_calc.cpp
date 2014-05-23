#include <iostream>
#include <string>

#include "ast.h"
#include "parser.h"

using namespace std;

int ast_calc(AstNode *root);

int compute_number(AstNode *num)
{
    return num->value;
}

int compute_addition(AstNode *add)
{
    vector<AstNode*> children = add->children;
    int size = children.size();
    int x = ast_calc(add->children.at(0));
    int y = ast_calc(add->children.at(1));

    return x + y;
}

int compute_subtraction(AstNode *sub)
{
    vector<AstNode*> children = sub->children;
    int size = children.size();
    int x = ast_calc(sub->children.at(0));
    int y = ast_calc(sub->children.at(1));

    return x - y;
}

int compute_multiplication(AstNode *mul)
{
    vector<AstNode*> children = mul->children;
    int size = children.size();
    int x = ast_calc(mul->children.at(0));
    int y = ast_calc(mul->children.at(1));

    return x * y;
}

int compute_division(AstNode *dv)
{
    vector<AstNode*> children = dv->children;
    int size = children.size();
    int x = ast_calc(dv->children.at(0));
    int y = ast_calc(dv->children.at(1));

    return x / y;
}

int compute_paren(AstNode *dv)
{
    vector<AstNode*> children = dv->children;
    int size = children.size();

    return ast_calc(children[1]);
}

int ast_calc(AstNode *root)
{
    int value = 0;

    switch (root->type) {
        case AST_NUMBER:
            return compute_number(root);
        case AST_ADDITION:
            return compute_addition(root);
        case AST_SUBTRACTION:
            return compute_subtraction(root);
        case AST_MULTIPLICATION:
            return compute_multiplication(root);
        case AST_DIVISION:
            return compute_division(root);
        case AST_PAREN:
            return compute_paren(root);
    }

    vector<AstNode*> children = root->children;
    int size = children.size();

    if (size == 1) {
        return ast_calc(children[0]);
    } else {
        cout << "Unexpected " << root->strhead << endl;
    }

    return value;
}

int main(int argc, const char **argv)
{
    if (argc == 1) {
        cout << "Usage: " << argv[0] << " <expression>" << endl;
        return 1;
    }

    AstNode *ast = parse_statement(argv[1]);

    printf("%d\n", ast_calc(ast));

    return 0;
}

