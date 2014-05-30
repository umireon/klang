#pragma once

#include "Binding.h"
#include "ast/AstNode.h"

class KFunctionAst : public KFunction {
public:
	Binding binding;
	AstNode *body;

	KFunctionAst(Binding b, AstNode *n) : binding(b), body(n) {};
	virtual ~KFunctionAst();

    enum Type get_type() { return FUNCTION; }
    std::string to_s() { return std::string("Function"); }

	KObject* invoke(std::vector<KObject*> args);
};
