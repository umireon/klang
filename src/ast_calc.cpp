#include <iostream>
#include <string>
#include <math.h>
#include <stdexcept>
#include <stdlib.h>

#include "ast.h"
#include "Parse.h"

using namespace std;

class FuncLog : public Function {
	Object* invoke(std::vector<Object*> args) {
		Number *num = dynamic_cast<Number*>(args.at(0));

		if (!num) {
			throw std::invalid_argument("Argument1 is not a number.");
		}

		return new Float(log(num->to_f()));
	}
};

class FuncLog10 : public Function {
	Object* invoke(std::vector<Object*> args) {
		Number *num = dynamic_cast<Number*>(args.at(0));

		if (!num) {
			throw std::invalid_argument("Argument1 is not a number.");
		}

		return new Float(log10(num->to_f()));
	}
};

class FuncExit : public Function {
	Object* invoke(std::vector<Object*> args) {
		exit(0);
	}
};

int main(int argc, const char **argv)
{
    Binding b;
    char line_buf[1024];
    b.set_local(std::string("log"), new FuncLog());
    b.set_local(std::string("log10"), new FuncLog10());
    b.set_local(std::string("exit"), new FuncExit());
    while (true) {
        Parse p;
        cout << "> ";
        cin.getline(line_buf, sizeof(line_buf));
        AstNode *ast = p.parse(line_buf);

        Object* res = ast->evaluate(&b);

        if (Integer* i = dynamic_cast<Integer*>(res)) {
	        cout << "Integer: " << i->to_i() << endl;
        }

        if (Float* f = dynamic_cast<Float*>(res)) {
	        cout << "Float: " << f->to_f() << endl;
        }
        
        if (Function* func = dynamic_cast<Function*>(res)) {
	        cout << "Function" << endl;
        }
        
        if (res == NULL) {
	        cout << "NULL" << endl;
        }
    }
}

