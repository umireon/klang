#include <iostream>
#include <string>
#include <typeinfo>

#include "ast.h"
#include "Parse.h"

using namespace std;

void print_ast(AstNode *node, int depth)
{
    string indent = string(depth * 4, ' ');
    string str = node->get_string();
    
    cout << indent << "- type: " << typeid(*node).name() << endl;
    cout << indent << "  str: " << str << endl;
    
    int size = node->size();
    if (size > 0) {
        AstParentNode *root = static_cast<AstParentNode*>(node);
        
        cout << indent << "  children: " << endl;
        
        for (int i = 0; i < size; i++) {
            print_ast(root->children[i], depth + 1);
        }
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
    AstNode *ast = p.parse(argv[1]);
    
    print_ast(ast, 0);
    
    return 0;
}

