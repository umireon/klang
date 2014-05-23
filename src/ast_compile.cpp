#include <iostream>
#include <string>
#include <typeinfo>

#include "ast.h"
#include "parser.h"

using namespace std;

void print_ast(AstNode *root, int depth)
{
    string indent = string(depth * 4, ' ');
    string str = string(root->strhead, root->strtail - root->strhead);

    cout << indent << "- type: " << typeid(*root).name() << endl;
    cout << indent << "  str: " << str << endl;
    cout << indent << "  value: " << root->value << endl;

    for (int i = 0; i < root->children.size(); i++) {
        print_ast(root->children.at(i), depth + 1);
    }
}

AstNode* ast_reduce(AstNode* root)
{
    vector<AstNode*> &children = root->children;
    int size = children.size();

    for (int i = 0; i < size; i++) {
        children[i] = ast_reduce(root->children.at(i));
    }

    enum node_type type = root->type;
    switch (type) {
    case AST_ADDITION:
        if (size == 2) {
            AstNode *x = children[0];
            AstNode *y = children[1];

            if (x->type == AST_NUMBER && y->type == AST_NUMBER) {
                AstNode *newRoot = new AstNode();
                newRoot->type = AST_NUMBER;
                newRoot->strhead = x->strhead;
                newRoot->strtail = y->strtail;
                newRoot->value = x->value + y->value;
                delete root;
                return newRoot;
            }
        }
        break;
    case AST_SUBTRACTION:
        if (size == 2) {
            AstNode *x = children[0];
            AstNode *y = children[1];

            if (x->type == AST_NUMBER && y->type == AST_NUMBER) {
                AstNode *newRoot = new AstNode();
                newRoot->type = AST_NUMBER;
                newRoot->strhead = x->strhead;
                newRoot->strtail = y->strtail;
                newRoot->value = x->value - y->value;
                delete root;
                return newRoot;
            }
        }
        break;
    case AST_MULTIPLICATION:
        if (size == 2) {
            AstNode *x = children[0];
            AstNode *y = children[1];

            if (x->type == AST_NUMBER && y->type == AST_NUMBER) {
                AstNode *newRoot = new AstNode();
                newRoot->type = AST_NUMBER;
                newRoot->strhead = x->strhead;
                newRoot->strtail = y->strtail;
                newRoot->value = x->value * y->value;
                delete root;
                return newRoot;
            }
        }
        break;
    case AST_DIVISION:
        if (size == 2) {
            AstNode *x = children[0];
            AstNode *y = children[1];

            if (x->type == AST_NUMBER && y->type == AST_NUMBER) {
                AstNode *newRoot = new AstNode();
                newRoot->type = AST_NUMBER;
                newRoot->strhead = x->strhead;
                newRoot->strtail = y->strtail;
                newRoot->value = x->value / y->value;
                delete root;
                return newRoot;
            }
        }
        break;
    case AST_PAREN:
        if (size == 3) {
            AstNode *newRoot = children[1];
            newRoot->strhead--;
            newRoot->strtail++;
            children.clear();
            delete root;
            return newRoot;
        }
        break;
    case AST_STATEMENT:
    case AST_EXPRESSION:
    case AST_TERM:
    case AST_ELEMENT:
        if (size == 1) {
            AstNode *newRoot = children[0];
            children.pop_back();
            delete root;
            return newRoot;
        }
        break;
    }

    return root;
}

int main(int argc, const char **argv)
{
    if (argc == 1) {
        cout << "Usage: " << argv[0] << " <expression>" << endl;
        return 1;
    }

    AstNode *ast = parse_statement(argv[1]);
    ast = ast_reduce(ast);
    print_ast(ast, 0);

    return 0;
}

