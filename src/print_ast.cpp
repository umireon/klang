#include <iostream>
#include <string>
#include <typeinfo>

#include "ast.h"
#include "Parse.h"

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

    Parse p;
    AstNode *ast = p.parse_statement(argv[1]);

    print_ast(ast, 0);

    return 0;
}

