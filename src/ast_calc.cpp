#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <math.h>
#include <stdexcept>
#include <algorithm>
#include <stdlib.h>
#include <editline/readline.h>
#include <boost/numeric/ublas/vector.hpp>

#include "ast.h"
#include "parser.h"
#include "kobject.h"

#include "kfunc/FuncExit.h"
#include "kfunc/FuncPrint.h"
#include "kfunc/FuncPuts.h"

#include "kfunc/FuncC.h"
#include "kfunc/FuncLog.h"
#include "kfunc/FuncLog10.h"
#include "kfunc/FuncMatrix.h"
#include "kfunc/triangle.h"
#include "kfunc/factorial.h"

using namespace std;
using namespace boost::numeric;

int main(int argc, const char **argv)
{
    FuncExit kExit;
    FuncPrint kPrint;
    FuncPuts kPuts;

    FuncLog kLog;
    FuncLog10 kLog10;
    FuncC kC;
    FuncMatrix kMatrix;

    FuncSin kSin;
    FuncCos kCos;
    FuncTan kTan;

    FuncSinh kSinh;
    FuncCosh kCosh;
    FuncTanh kTanh;

    FuncArcsin kArcsin;
    FuncArccos kArccos;
    FuncArctan kArctan;

    FuncFact kFact;
    FuncPerm kPerm;
    FuncComb kComb;
    FuncHmpr kHmpr;

    Binding b;
    const char *line;
    b.set_local(std::string("exit"), &kExit);
    b.set_local(std::string("print"), &kPrint);
    b.set_local(std::string("puts"), &kPuts);

    b.set_local(std::string("log"), &kLog);
    b.set_local(std::string("log10"), &kLog10);
    b.set_local(std::string("c"), &kC);
    b.set_local(std::string("matrix"), &kMatrix);

    b.set_local(std::string("sin"), &kSin);
    b.set_local(std::string("cos"), &kCos);
    b.set_local(std::string("tan"), &kTan);

    b.set_local(std::string("sinh"), &kSinh);
    b.set_local(std::string("cosh"), &kCosh);
    b.set_local(std::string("tanh"), &kTanh);

    b.set_local(std::string("arcsin"), &kArcsin);
    b.set_local(std::string("arccos"), &kArccos);
    b.set_local(std::string("arctan"), &kArctan);

    b.set_local(std::string("fact"), &kArcsin);
    b.set_local(std::string("arccos"), &kArccos);
    b.set_local(std::string("arctan"), &kArctan);

    b.set_local(std::string("fact"), &kFact);
    b.set_local(std::string("perm"), &kPerm);
    b.set_local(std::string("comb"), &kComb);
    b.set_local(std::string("hmpr"), &kHmpr);

    int lines = 1;
    int depth = 0;
    ostringstream buf;
    while (true) {
        Parse p;
        ostringstream os;
        os << "klang:";
        os.setf(std::ios::right);
        os.fill('0');
        os.width(3);
        os << lines;
        os << ":" << depth << "> ";
        line = readline(os.str().c_str());
        lines++;

        if (std::strrchr(line, '{')) {
            depth++;
        }
        if (depth > 0 && std::strrchr(line, '}')) {
            depth--;
        }

        buf << line << std::endl;

        if (depth > 0) {
            continue;
        }

        add_history(buf.str().c_str());

        line = current_history()->line;

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
                //std::vector<KObject*> args;
                //func->invoke(args);
                cout << "Function" << endl;
            }
            
            if (res == NULL) {
                cout << "NULL" << endl;
            } else {
                cout << res->to_s() << endl;
            }
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
        }

        buf.str("");
    }
}

