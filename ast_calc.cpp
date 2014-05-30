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

class FuncMatrix : public KFunction{
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

class FuncC : public KFunction{
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

//正弦系の関数
class FuncSine : public KFunction {
	KObject* invoke(std::vector<KObject*> args) {
		KNumber *num = dynamic_cast<KNumber*>(args.at(0));
        
        if (args.size() != 1) {
			throw std::invalid_argument("Arity: 1");
        }

		if (!num) {
			throw std::invalid_argument("Argument1 is not a KNumber.");
		}

		return new KFloat(sin(num->to_f()));
	}
};
class FuncArcsine : public KFunction {
	KObject* invoke(std::vector<KObject*> args) {
		KNumber *num = dynamic_cast<KNumber*>(args.at(0));
        
        if (args.size() != 1) {
			throw std::invalid_argument("Arity: 1");
        }

		if (!num) {
			throw std::invalid_argument("Argument1 is not a KNumber.");
		}

		return new KFloat(asin(num->to_f()));
	}
};
class FuncHysine : public KFunction {
	KObject* invoke(std::vector<KObject*> args) {
		KNumber *num = dynamic_cast<KNumber*>(args.at(0));
        
        if (args.size() != 1) {
			throw std::invalid_argument("Arity: 1");
        }

		if (!num) {
			throw std::invalid_argument("Argument1 is not a KNumber.");
		}

		return new KFloat(sinh(num->to_f()));
	}
};

//余弦系
class FuncCosine : public KFunction {
	KObject* invoke(std::vector<KObject*> args) {
		KNumber *num = dynamic_cast<KNumber*>(args.at(0));
        
        if (args.size() != 1) {
			throw std::invalid_argument("Arity: 1");
        }

		if (!num) {
			throw std::invalid_argument("Argument1 is not a KNumber.");
		}

		return new KFloat(cos(num->to_f()));
	}
};
class FuncArccosine : public KFunction {
	KObject* invoke(std::vector<KObject*> args) {
		KNumber *num = dynamic_cast<KNumber*>(args.at(0));
        
        if (args.size() != 1) {
			throw std::invalid_argument("Arity: 1");
        }

		if (!num) {
			throw std::invalid_argument("Argument1 is not a KNumber.");
		}

		return new KFloat(acos(num->to_f()));
	}
};
class FuncHycosine : public KFunction {
	KObject* invoke(std::vector<KObject*> args) {
		KNumber *num = dynamic_cast<KNumber*>(args.at(0));
        
        if (args.size() != 1) {
			throw std::invalid_argument("Arity: 1");
        }

		if (!num) {
			throw std::invalid_argument("Argument1 is not a KNumber.");
		}

		return new KFloat(cosh(num->to_f()));
	}
};

//正接系
class FuncTangent : public KFunction {
	KObject* invoke(std::vector<KObject*> args) {
		KNumber *num = dynamic_cast<KNumber*>(args.at(0));
        
        if (args.size() != 1) {
			throw std::invalid_argument("Arity: 1");
        }

		if (!num) {
			throw std::invalid_argument("Argument1 is not a KNumber.");
		}

		return new KFloat(tan(num->to_f()));
	}
};
class FuncArctangent : public KFunction {
	KObject* invoke(std::vector<KObject*> args) {
		KNumber *num = dynamic_cast<KNumber*>(args.at(0));
        
        if (args.size() != 1) {
			throw std::invalid_argument("Arity: 1");
        }

		if (!num) {
			throw std::invalid_argument("Argument1 is not a KNumber.");
		}

		return new KFloat(atan(num->to_f()));
	}
};
class FuncHytangent : public KFunction {
	KObject* invoke(std::vector<KObject*> args) {
		KNumber *num = dynamic_cast<KNumber*>(args.at(0));
        
        if (args.size() != 1) {
			throw std::invalid_argument("Arity: 1");
        }

		if (!num) {
			throw std::invalid_argument("Argument1 is not a KNumber.");
		}

		return new KFloat(tanh(num->to_f()));
	}
};

int kaijo(int k){
	if(k!=0){
		return k*kaijo(k-1);
	}else{
		return 1;
	}
}

//階乗
class FuncFactorial : public KFunction {
	KObject* invoke(std::vector<KObject*> args) {
		KNumber *num = dynamic_cast<KNumber*>(args.at(0));
        
        if (args.size() != 1) {
			throw std::invalid_argument("Arity: 1");
        }

		if (!num) {
			throw std::invalid_argument("Argument1 is not a KNumber.");
		}

		return new KFloat(kaijo((int)(num->to_f())));
	}
};

//順列nPr
class FuncPerm : public KFunction {
	KObject* invoke(std::vector<KObject*> args) {
		KNumber *num1 = dynamic_cast<KNumber*>(args.at(0));
		KNumber *num2 = dynamic_cast<KNumber*>(args.at(1));
		int n,r;
        
        if (args.size() != 2) {
			throw std::invalid_argument("Arity: 1");
        }

		if (!num1) {
			throw std::invalid_argument("Argument1 is not a KNumber.");
		}
		if (!num2) {
			throw std::invalid_argument("Argument2 is not a KNumber.");
		}

		n=num1->to_f();
		r=num2->to_f();

		return new KFloat( kaijo(n) / kaijo(r) );
	}
};


//組み合わせnCr
class FuncComb : public KFunction {
	KObject* invoke(std::vector<KObject*> args) {
		KNumber *num1 = dynamic_cast<KNumber*>(args.at(0));
		KNumber *num2 = dynamic_cast<KNumber*>(args.at(1));
		int n,r;
        
        if (args.size() != 2) {
			throw std::invalid_argument("Arity: 1");
        }

		if (!num1) {
			throw std::invalid_argument("Argument1 is not a KNumber.");
		}
		if (!num2) {
			throw std::invalid_argument("Argument2 is not a KNumber.");
		}
		n=num1->to_f();
		r=num2->to_f();

		return new KFloat( kaijo(n) / kaijo(r) / kaijo(n-r));
	}
};

//重複あり組み合わせnHr
class FuncHmpr : public KFunction {
	KObject* invoke(std::vector<KObject*> args) {
		KNumber *num1 = dynamic_cast<KNumber*>(args.at(0));
		KNumber *num2 = dynamic_cast<KNumber*>(args.at(1));
		int n,r;
        
        if (args.size() != 2) {
			throw std::invalid_argument("Arity: 1");
        }

		if (!num1) {
			throw std::invalid_argument("Argument1 is not a KNumber.");
		}
		if (!num2) {
			throw std::invalid_argument("Argument2 is not a KNumber.");
		}
		n=num1->to_f();
		r=num2->to_f();

		return new KFloat( kaijo(n+r-1) / kaijo(r));
	}
};

int main(int argc, const char **argv)
{
    FuncLog kLog;
    FuncLog10 kLog10;
    FuncExit kExit;
    FuncC kC;
    FuncMatrix kMatrix;
//三角関数・逆三角関数・双曲線関数
    FuncSine kSine;
    FuncArcsine kArcsine;
    FuncHysine kHysine;

    FuncCosine kCosine;
    FuncArccosine kArccosine;
    FuncHycosine kHycosine;

    FuncTangent kTangent;
    FuncArctangent kArctangent;
    FuncHytangent kHytangent;

    FuncFactorial kFactorial;
    FuncPerm kPerm;
    FuncComb kComb;
    FuncHmpr kHmpr;

    Binding b;
    char *line;
    b.set_local(std::string("log"), &kLog);
    b.set_local(std::string("log10"), &kLog10);
    b.set_local(std::string("exit"), &kExit);
    b.set_local(std::string("c"), &kC);
    b.set_local(std::string("matrix"), &kMatrix);

    b.set_local(std::string("sin"), &kSine);
    b.set_local(std::string("arcsin"), &kArcsine);
    b.set_local(std::string("sinh"), &kHysine);

    b.set_local(std::string("cos"), &kCosine);
    b.set_local(std::string("arccos"), &kArccosine);
    b.set_local(std::string("cosh"), &kHycosine);

    b.set_local(std::string("tan"), &kTangent);
    b.set_local(std::string("arctan"), &kArctangent);
    b.set_local(std::string("tanh"), &kHytangent);

    b.set_local(std::string("Fact"), &kFactorial);	//階乗
    b.set_local(std::string("Perm"), &kPerm);	//順列
    b.set_local(std::string("Comb"), &kComb);	//組み合わせ
    b.set_local(std::string("Hmpr"), &kHmpr);	//重複あり組み合わせ



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
