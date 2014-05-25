#include <iostream>
#include <string>

#include "ast.h"
#include "Parse.h"

using namespace std;

int main(int argc, const char **argv)
{
    Binding b;
    while (true) {
        Parse p;
        string line;
        cout << "> ";
        cin >> line;
        AstNode *ast = p.parse(line.c_str());
        
        cout << "double: " << ast->get_double(&b) << endl;
    }
}

