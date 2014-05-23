#include <iostream>
#include <string>

#include "ast.h"
#include "parser.h"

using namespace std;

void print_ast(AstNode *root, int depth)
{
    string indent = string(depth * 4, ' ');
    string str = string(root->strhead, root->strtail - root->strhead);

    switch (root->type) {
        case AST_NUMBER:
            cout << indent << "- type: AST_NUMBER" << endl;
            cout << indent << "  str: " << str << endl;
            cout << indent << "  value: " << root->value << endl;
            break;
        case AST_EXPRESSION:
            cout << indent << "- type: AST_EXPRESSION" << endl;
            cout << indent << "  str: " << str << endl;
            cout << indent << "  children:" << endl;
            break;
        case AST_ADDITION:
            cout << indent << "- type: AST_ADDITION" << endl;
            cout << indent << "  str: " << str << endl;
            cout << indent << "  children:" << endl;
            break;
        case AST_SUBTRACTION:
            cout << indent << "- type: AST_SUBTRACTION" << endl;
            cout << indent << "  str: " << str << endl;
            cout << indent << "  children:" << endl;
            break;
        case AST_TERM:
            cout << indent << "- type: AST_TERM" << endl;
            cout << indent << "  str: " << str << endl;
            cout << indent << "  children:" << endl;
            break;
        case AST_MULTIPLICATION:
            cout << indent << "- type: AST_MULTIPLICATION" << endl;
            cout << indent << "  str: " << str << endl;
            cout << indent << "  children:" << endl;
            break;
        case AST_DIVISION:
            cout << indent << "- type: AST_DIVISION" << endl;
            cout << indent << "  str: " << str << endl;
            cout << indent << "  children:" << endl;
            break;
        case AST_STATEMENT:
            cout << indent << "- type: AST_STATEMENT" << endl;
            cout << indent << "  str: " << str << endl;
            cout << indent << "  children:" << endl;
            break;
        case AST_PAREN_LEFT:
            cout << indent << "- type: AST_PAREN_LEFT" << endl;
            cout << indent << "  str: " << str << endl;
            break;
        case AST_PAREN_RIGHT:
            cout << indent << "- type: AST_PAREN_RIGHT" << endl;
            cout << indent << "  str: " << str << endl;
            break;
        case AST_PAREN:
            cout << indent << "- type: AST_PAREN" << endl;
            cout << indent << "  str: " << str << endl;
            cout << indent << "  children:" << endl;
            break;
        case AST_STUB:
            cout << indent << "- type: AST_STUB" << endl;
            cout << indent << "  str: " << str << endl;
            cout << indent << "  children:" << endl;
            break;
        case AST_ELEMENT:
            cout << indent << "- type: AST_ELEMENT" << endl;
            cout << indent << "  str: " << str << endl;
            cout << indent << "  children:" << endl;
            break;
        case AST_UNKNOWN:
        default:
            cout << indent << "- type: AST_UNKNOWN" << endl;
            cout << indent << "  str: " << str << endl;
            break;

    }

    for (int i = 0; i < root->children.size(); i++) {
        print_ast(root->children.at(i), depth + 1);
    }
}

void print_ast(AstNode *root)
{
    print_ast(root, 0);
}

int main(int argc, const char **argv)
{
    if (argc == 1) {
        cout << "Usage: " << argv[0] << " <expression>" << endl;
        return 1;
    }

    AstNode *ast = parse_statement(argv[1]);

    print_ast(ast, 0);

    return 0;
}

