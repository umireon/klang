#include <iostream>
#include <string>
#include <math.h>
#include <stdexcept>
#include <stdlib.h>
#include <editline/readline.h>
#include <boost/numeric/ublas/vector.hpp>

#include "ast.h"
#include "parser.h"
#include "kobject.h"

#include "kfunc/FuncC.h"
#include "kfunc/FuncExit.h"
#include "kfunc/FuncLog.h"
#include "kfunc/FuncLog10.h"
#include "kfunc/FuncMatrix.h"

using namespace std;
using namespace boost::numeric;

int main(int argc, const char **argv)
{
    FuncLog kLog;
    FuncLog10 kLog10;
    FuncExit kExit;
    FuncC kC;
    FuncMatrix kMatrix;

    Binding b;
    char *line;
    b.set_local(std::string("log"), &kLog);
    b.set_local(std::string("log10"), &kLog10);
    b.set_local(std::string("exit"), &kExit);
    b.set_local(std::string("c"), &kC);
    b.set_local(std::string("matrix"), &kMatrix);

    while (true) {
        Parse p;
        line = readline("> ");
        add_history(line);

        try {
            AstNode *ast = p.parse(line);
            
            if (ast == NULL) {
                continue;
            }

            KObject* res = ast->evaluate(&b);
            
            if (KInteger* i = dynamic_cast<KInteger*>(res)) {
                cout << "Integer: " << i->to_i() << endl;
            }
            
            if (KFloat* f = dynamic_cast<KFloat*>(res)) {
                cout << "KFloat: " << f->to_f() << endl;
            }
            
            if (KFunction* func = dynamic_cast<KFunction*>(res)) {
                std::vector<KObject*> args;
                func->invoke(args);
                cout << "Function" << endl;
            }
            
            if (res == NULL) {
                cout << "NULL" << endl;
            } else {
                cout << res->to_s() << endl;
            }
        } catch (std::exception& e) {
            std::cerr << e.what();
            continue;
        }
    }
}

