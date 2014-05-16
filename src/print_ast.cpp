#include <iostream>
#include <string>

extern "C" {
#include "parser.h"
}

using namespace std;

void print_ast(struct ast_node *root, int depth)
{
    string indent = string(depth * 4, ' ');

    switch (root->type) {
        case AST_NUMBER:
            cout << indent << "- type: AST_NUMBER"<< endl;
            cout << indent << "  value: " << root->value << endl;
            break;
        case AST_TERM:
            cout << indent << "- type: AST_TERM"<< endl;
            cout << indent << "  children:" << endl;
            break;
        case AST_MULTIPLICATION:
            cout << indent << "- type: AST_MULTIPLICATION"<< endl;
            cout << indent << "  children:" << endl;
            break;
        case AST_DIVISION:
            cout << indent << "- type: AST_DIVISION"<< endl;
            cout << indent << "  children:" << endl;
            break;
        case AST_STATEMENT:
            cout << "- type: AST_STATEMENT"<< endl;
            cout << "  children:" << endl;
            break;
    }

    for (int i = 0; i < root->num_of_child; i++) {
        print_ast(root->children[i], depth + 1);
    }
}

void print_ast(struct ast_node *root)
{
    print_ast(root, 0);
}

int main(int argc, const char **argv)
{
    if (argc == 1) {
        cout << "Usage: " << argv[0] << " <expression>" << endl;
        exit(1);
    }

    struct ast_node *ast = parse_statement(argv[1]);

    print_ast(ast, 0);

    return 0;
}

