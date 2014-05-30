#include "ast/AstFunction.h"

AstFunction::~AstFunction(void)
{
	delete astParam;
	delete body;
}

KFunctionAst* AstFunction::evaluate(Binding *b)
{
	return new KFunctionAst(*b, body);
}
