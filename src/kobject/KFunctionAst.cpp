#include "kobject/KFunctionAst.h"

KFunctionAst::~KFunctionAst()
{
}

KObject* KFunctionAst::invoke(std::vector<KObject*> args) {
    Binding b(binding);

	return body->evaluate(&b);
}
