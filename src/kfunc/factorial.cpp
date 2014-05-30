#include "kobject.h"

#include "kfunc/factorial.h"

KObject* FuncFact::invoke(std::vector<KObject*> args) {
	KNumber *num = dynamic_cast<KNumber*>(args.at(0));
    
    if (args.size() != 1) {
		throw std::invalid_argument("Arity: 1");
    }

	if (!num) {
		throw std::invalid_argument("Argument1 is not a KNumber.");
	}

	long fact = factorial(num->to_i());

	return new KInteger(fact);
}


long FuncFact::factorial(long n){
	long fact = 1;

	while (n > 0) {
		fact = fact * n;
		n--;
	}

	return fact;
}

KObject* FuncPerm::invoke(std::vector<KObject*> args) {
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

	n=num1->to_i();
	r=num2->to_i();

	return new KInteger(factorial(n)/factorial(r));
}

KObject* FuncComb::invoke(std::vector<KObject*> args) {
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
	n=num1->to_i();
	r=num2->to_i();

	return new KInteger(factorial(n)/factorial(r)/factorial(n-r));
}

KObject* FuncHmpr::invoke(std::vector<KObject*> args) {
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
	n=num1->to_i();
	r=num2->to_i();

	return new KInteger(factorial(n+r-1)/factorial(r));
}
