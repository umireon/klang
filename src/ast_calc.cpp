#include <iostream>
#include <string>
#include <math.h>
#include <stdexcept>
#include <stdlib.h>
#include <editline/readline.h>
#include <boost/numeric/ublas/vector.hpp>

#include "ast.h"
#include "parser.h"

using namespace std;
using namespace boost::numeric;

class FuncMatrix : public KFunction {
    KMatrix* invoke(std::vector<KObject*> args) {
        KVector *kvect = dynamic_cast<KVector*>(args[0]);
        long nrow = static_cast<KNumber*>(args[1])->to_i();
        long ncol = static_cast<KNumber*>(args[2])->to_i();

        dvector::iterator iter = kvect->vect.begin();

        dmatrix m = dmatrix(nrow, ncol);

        for (long i = 0; i < nrow; i++) {
            for (long j = 0; j < ncol; j++) {
                m(i,j) = *iter;
                iter++;
            }
        }

        return new KMatrix(m);
    }
};

class FuncC : public KFunction {
	KVector* invoke(std::vector<KObject*> args) {
        dvector vect(args.size());

        for (int i = 0; i < args.size(); i++) {
            KNumber *knum = dynamic_cast<KNumber*>(args[i]);
            if (knum == NULL) {
                throw std::invalid_argument(std::string("not a number"));
            }
            vect[i] = knum->to_f();
        }

		return new KVector(vect);
	}
};

class FuncLog : public KFunction {
	KObject* invoke(std::vector<KObject*> args) {
		KNumber *num = dynamic_cast<KNumber*>(args.at(0));
        
        if (args.size() != 1) {
			throw std::invalid_argument("Arity: 1");
        }

		if (!num) {
			throw std::invalid_argument("Argument1 is not a KNumber.");
		}

		return new KFloat(log(num->to_f()));
	}
};

class FuncLog10 : public KFunction {
	KObject* invoke(std::vector<KObject*> args) {
		KNumber *num = dynamic_cast<KNumber*>(args.at(0));
        
        if (args.size() != 1) {
			throw std::invalid_argument("Arity: 1");
        }
        
		if (!num) {
			throw std::invalid_argument("Argument1 is not a KNumber.");
		}

		return new KFloat(log10(num->to_f()));
	}
};

class FuncExit : public KFunction {
	KObject* invoke(std::vector<KObject*> args) {
		exit(0);
	}
};

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

