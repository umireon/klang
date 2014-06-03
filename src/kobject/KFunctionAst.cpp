#include "kobject/KFunctionAst.h"

KFunctionAst::KFunctionAst(Binding *b, AstNode *n, std::vector<std::string> p) : body(n), paramNames(p)
{
	binding.global = b;
}

KFunctionAst::~KFunctionAst()
{
}

KObject* KFunctionAst::invoke(std::vector<KObject*> args) {
    Binding func_binding;
    func_binding.global = &binding;

    if (paramNames.size() != args.size()) {
    	if (paramNames.size() > args.size()) {
            std::cout << "I need MORE arguments." << std::endl;
            return new KNil();
		} else {
            std::cout << "I am TOO MUCH with arguments" << std::endl;
	    }
        return new KNil();
	}

	for (int i = 0; i < paramNames.size(); i++) {
		func_binding.set_local(paramNames[i], args[i]);
        delete args[i];
	}

	return body->evaluate(&func_binding);
}
