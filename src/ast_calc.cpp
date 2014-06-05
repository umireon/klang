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
    
    FuncMath kLog(&std::log);
    FuncMath kLog10(&std::cos);
    b->set_local(std::string("log"), &kLog);
    b->set_local(std::string("log10"), &kLog10);

    FuncMath kSin(&std::sin);
    FuncMath kCos(&std::cos);
    FuncMath kTan(&std::tan);
    b->set_local(std::string("sin"), &kSin);
    b->set_local(std::string("cos"), &kCos);
    b->set_local(std::string("tan"), &kTan);
    
    FuncMath kSinh(&std::sinh);
    FuncMath kCosh(&std::cosh);
    FuncMath kTanh(&std::tanh);
    b->set_local(std::string("sinh"), &kSinh);
    b->set_local(std::string("cosh"), &kCosh);
    b->set_local(std::string("tanh"), &kTanh);
    
    FuncMath kArcsin(&std::sinh);
    FuncMath kArccos(&std::cosh);
    FuncMath kArctan(&std::tanh);
    b->set_local(std::string("arcsin"), &kArcsin);
    b->set_local(std::string("arccos"), &kArccos);
    b->set_local(std::string("arctan"), &kArctan);
    
    FuncFact kFact;
    FuncPerm kPerm;
    FuncComb kComb;
    FuncHmpr kHmpr;
    b->set_local(std::string("fact"), &kFact);
    b->set_local(std::string("perm"), &kPerm);
    b->set_local(std::string("comb"), &kComb);
    b->set_local(std::string("hmpr"), &kHmpr);

    KFloat cPI(3.14159265358979323846);
    KFloat cE(2.7182818284590452354);
	b->set_local(std::string("PI"), &cPI);
	b->set_local(std::string("E"), &cE);

    //physical constants

    KFloat cC(299792458);
    KFloat cNA(6.02214129*pow(10,23));
    KFloat cR(8.3144621);
    KFloat cF(96485.3365);
    KFloat cG(6.67384*pow(10,-11));
    KFloat cH(6.62606957*pow(10,-34));
    KFloat cK(1.3806488*pow(10,-23));
    KFloat cRYDBERG_CONST(10973731.568539);
    KFloat cE0(8.85418782*pow(10,-12));
    KFloat cMU0(8.85418782*pow(10,-12));
    KFloat cEC(1.60217657*pow(10,-19));
    KFloat cMACH(340.29);
    KFloat cGRAVITY_EARTH(9.80665);
    b->set_local(std::string("C"), &cC);  //speed of light
    b->set_local(std::string("NA"), &cNA);    //Avogadro's constant
    b->set_local(std::string("R"), &cR);              //Air constant
    b->set_local(std::string("F"), &cF);             //Faraday constant
    b->set_local(std::string("G"), &cG);        //banyuuinryokuteisuu
    b->set_local(std::string("H"), &cH);     //Planck's consntan
    b->set_local(std::string("K"), &cK);      //Boltzmann constant
    b->set_local(std::string("RYDBERG_CONST"), &cRYDBERG_CONST);    //Rydberg consntant
    b->set_local(std::string("E0"), &cE0);   //e0
    b->set_local(std::string("MU0"), &cMU0);   //mu0
    b->set_local(std::string("EC"), &cEC);   //elementary charge
    b->set_local(std::string("MACH"), &cMACH);  //speed of sound
    b->set_local(std::string("GRAVITY_EARTH"), &cGRAVITY_EARTH);    //gravity on earth
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
