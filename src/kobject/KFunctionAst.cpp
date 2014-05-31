#include "kobject/KFunctionAst.h"

KFunctionAst::KFunctionAst(Binding *b, AstNode *n, std::vector<std::string> p) : body(n), paramNames(p)
{
	binding.global = b;
}

KFunctionAst::~KFunctionAst()
{
	delete body;
}

KObject* KFunctionAst::invoke(std::vector<KObject*> args) {
    Binding func_binding;
    func_binding.global = &binding;

    if (paramNames.size() != args.size()) {
    	if (paramNames.size() > args.size()) {
	        throw std::invalid_argument("I need MORE arguments.");
		} else {
	        throw std::invalid_argument("I am TOO MUCH with arguments");
	    }
	}

	for (int i = 0; i < paramNames.size(); i++) {
		func_binding.set_local(paramNames[i], args[i]);
	}

	return body->evaluate(&func_binding);
}
