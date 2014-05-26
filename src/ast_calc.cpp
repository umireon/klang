#include <iostream>
#include <string>
#include <math.h>
#include <stdexcept>
#include <stdlib.h>
#include <editline/readline.h>

#include "parser/ast.h"
#include "parser/Parse.h"

using namespace std;

class FuncLog : public KFunction {
	Object* invoke(std::vector<Object*> args) {
		Number *num = dynamic_cast<Number*>(args.at(0));
        
        if (args.size() != 1) {
			throw std::invalid_argument("Arity: 1");
        }

		if (!num) {
			throw std::invalid_argument("Argument1 is not a number.");
		}

		return new Float(log(num->to_f()));
	}
};

class FuncLog10 : public KFunction {
	Object* invoke(std::vector<Object*> args) {
		Number *num = dynamic_cast<Number*>(args.at(0));
        
        if (args.size() != 1) {
			throw std::invalid_argument("Arity: 1");
        }
        
		if (!num) {
			throw std::invalid_argument("Argument1 is not a number.");
		}

		return new Float(log10(num->to_f()));
	}
};

class FuncExit : public KFunction {
	Object* invoke(std::vector<Object*> args) {
		exit(0);
	}
};

int main(int argc, const char **argv)
{
    FuncLog kLog;
    FuncLog10 kLog10;
    FuncExit kExit;

    Binding b;
    char *line;
    b.set_local(std::string("log"), &kLog);
    b.set_local(std::string("log10"), &kLog10);
    b.set_local(std::string("exit"), &kExit);

    while (true) {
        Parse p;
        line = readline("> ");
        add_history(line);

        try {
            AstNode *ast = p.parse(line);
            
            if (ast == NULL) {
                continue;
            }

            Object* res = ast->evaluate(&b);
            
            if (Integer* i = dynamic_cast<Integer*>(res)) {
                cout << "Integer: " << i->to_i() << endl;
            }
            
            if (Float* f = dynamic_cast<Float*>(res)) {
                cout << "Float: " << f->to_f() << endl;
            }
            
            if (KFunction* func = dynamic_cast<KFunction*>(res)) {
                std::vector<Object*> args;
                func->invoke(args);
                cout << "Function" << endl;
            }
            
            if (res == NULL) {
                cout << "NULL" << endl;
            }
        } catch (std::exception& e) {
            std::cerr << e.what();
            continue;
        }
    }
}

