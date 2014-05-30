#include "kobject/KFunctionAst.h"

KFunctionAst::~KFunctionAst()
{
	delete body;
}

KObject* KFunctionAst::invoke(std::vector<KObject*> args) {
    Binding b(binding);

    if (paramNames.size() != args.size()) {
    	if (paramNames.size() < args.size()) {
	        throw std::invalid_argument("I need MORE arguments.");
		} else {
	        throw std::invalid_argument("I am TOO MUCH with arguments");
	    }
	}

	for (int i = 0; i < paramNames.size(); i++) {
		b.set_local(paramNames[i], args[i]);
	}

	return body->evaluate(&b);
}

void KFunctionAst::bind(Binding &b) {
	binding = b;
}
