#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <cmath>
#include <stdexcept>
#include <algorithm>
#include <stdlib.h>
#include <vector>
#include <editline/readline.h>
#include <boost/numeric/ublas/vector.hpp>

#include "ast.h"
#include "parser/Parse.h"
#include "kobject.h"

#include "kfunc/FuncExit.h"
#include "kfunc/FuncPrint.h"
#include "kfunc/FuncPuts.h"
#include "kfunc/FuncFor.h"

#include "kfunc/FuncAnd.h"
#include "kfunc/FuncOr.h"
#include "kfunc/FuncNot.h"

#include "kfunc/FuncC.h"
#include "kfunc/FuncSeq.h"
#include "kfunc/FuncSum.h"
#include "kfunc/FuncProd.h"
#include "kfunc/FuncMatrix.h"

#include "kfunc/FuncLog.h"
#include "kfunc/FuncLog10.h"
#include "kfunc/triangle.h"
#include "kfunc/factorial.h"

using namespace std;
using namespace boost::numeric;

void make_world(Binding *b)
{
    FuncExit kExit;
    FuncPrint kPrint(std::cout);
    FuncPuts kPuts(std::cout);
    FuncFor kFor;
    
    FuncAnd kAnd;
    FuncOr kOr;
    FuncNot kNot;

    FuncC kC;
    FuncSum kSum;
    FuncSeq kSeq;
    FuncProd kProd;
    FuncMatrix kMatrix;
    
    FuncLog kLog;
    FuncLog10 kLog10;
    
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
    
    b->set_local(std::string("exit"), &kExit);
    b->set_local(std::string("print"), &kPrint);
    b->set_local(std::string("puts"), &kPuts);
    b->set_local(std::string("for"), &kFor);

    b->set_local(std::string("and"), &kAnd);
    b->set_local(std::string("or"), &kOr);
    b->set_local(std::string("not"), &kNot);

    b->set_local(std::string("c"), &kC);
    b->set_local(std::string("sum"), &kSum);
    b->set_local(std::string("seq"), &kSeq);
    b->set_local(std::string("prod"), &kSum);
    b->set_local(std::string("matrix"), &kMatrix);
    
    b->set_local(std::string("log"), &kLog);
    b->set_local(std::string("log10"), &kLog10);
    
    b->set_local(std::string("sin"), &kSin);
    b->set_local(std::string("cos"), &kCos);
    b->set_local(std::string("tan"), &kTan);
    
    b->set_local(std::string("sinh"), &kSinh);
    b->set_local(std::string("cosh"), &kCosh);
    b->set_local(std::string("tanh"), &kTanh);
    
    b->set_local(std::string("arcsin"), &kArcsin);
    b->set_local(std::string("arccos"), &kArccos);
    b->set_local(std::string("arctan"), &kArctan);
    
    b->set_local(std::string("fact"), &kArcsin);
    b->set_local(std::string("arccos"), &kArccos);
    b->set_local(std::string("arctan"), &kArctan);
    
    b->set_local(std::string("fact"), &kFact);
    b->set_local(std::string("perm"), &kPerm);
    b->set_local(std::string("comb"), &kComb);
    b->set_local(std::string("hmpr"), &kHmpr);

	b->set_local(std::string("PI"), new KFloat(3.14159265358979323846));
	b->set_local(std::string("E"), new KFloat(2.7182818284590452354));

    //physical constants
    b->set_local(std::string("C"), new KFloat(299792458));  //speed of light
    b->set_local(std::string("NA"), new KFloat(6.02214129*pow(10,23)));    //Avogadro's constant
    b->set_local(std::string("R"), new KFloat(8.3144621));              //Air constant
    b->set_local(std::string("F"), new KFloat(96485.3365));             //Faraday constant
    b->set_local(std::string("G"), new KFloat(6.67384*pow(10,-11)));        //banyuuinryokuteisuu
    b->set_local(std::string("H"), new KFloat(6.62606957*pow(10,-34)));     //Planck's consntan
    b->set_local(std::string("K"), new KFloat(1.3806488*pow(10,-23)));      //Boltzmann constant
    b->set_local(std::string("RYDBERG_CONST"), new KFloat(10973731.568539));    //Rydberg consntant
    b->set_local(std::string("E0"), new KFloat(8.85418782*pow(10,-12)));   //e0
    b->set_local(std::string("MU0"), new KFloat(1.25663706*pow(10,-6)));   //mu0
    b->set_local(std::string("EC"), new KFloat(1.60217657*pow(10,-19)));   //elementary charge
    b->set_local(std::string("MACH"), new KFloat(340.29));  //speed of sound

    b->set_local(std::string("GRAVITY_EARTH"), new KFloat(9.80665));    //gravity on earth
}

std::string create_prompt(int lineno, int depth)
{
    ostringstream os;
    os << "klang:";
    os.setf(std::ios::right);
    os.fill('0');
    os.width(3);
    os << lineno;
    os << ":" << depth << "> ";
    
    return os.str();
}

int run()
{
    
    Binding binding;
    Binding *b = &binding;
	std::vector<std::string> lines;
    
    make_world(b);
    
    int lineno = 1;
    int depth = 0;
    ostringstream buf;
    while (true) {
        std::string prompt = create_prompt(lineno, depth);
        std::string input_buf(readline(prompt.c_str()));
		lineno++;
        
        
        depth += std::count(input_buf.begin(), input_buf.end(), '{');
        depth -= std::count(input_buf.begin(), input_buf.end(), '}');
        
        buf << input_buf << std::endl;
        
        if (depth > 0) {
            continue;
		}
        
		lines.push_back(buf.str());
        
        std::string &line = lines[lines.size()-1];
        buf.str("");
        depth = 0;
        
		add_history(const_cast<char *>(line.c_str()));
        
        Parse p;
        SyntaxErrorHandler seh;
        seh.line = &line;
        seh.lineno = lineno;
        p.syntaxErrorHandler = &seh;
        
        try {
            AstNode *ast = p.parse(line.begin());
        
            if (ast == NULL) {
                continue;
            }
        
        
            KObject* res = ast->evaluate(b);
            
            if (res == NULL) {
                cout << "NULL" << endl;
            } else {
                cout << endl << "#=> " << res->to_s() << endl;
            }
        } catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }
}

int main()
{
    run();
}
