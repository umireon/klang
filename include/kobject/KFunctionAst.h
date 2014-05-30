#pragma once

#include <vector>

#include "Binding.h"
#include "ast/AstNode.h"

class KFunctionAst : public KFunction {
public:
	Binding binding;
	AstNode *body;
	std::vector<std::string> paramNames;

	KFunctionAst(Binding b, AstNode *n, std::vector<std::string> p) : binding(b), body(n), paramNames(p) {};
	virtual ~KFunctionAst();

    enum Type get_type() { return FUNCTION; }
    std::string to_s() { return std::string("Function"); }

	KObject* invoke(std::vector<KObject*> args);
};
