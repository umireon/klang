#pragma once

#include "kobject/KFunctionAst.h"

#include "ast/AstNode.h"
#include "ast/AstParameter.h"

class AstFunction : public AstNode {
public:
	AstParameter *astParam;
	AstNode *body;

	virtual ~AstFunction();
	virtual KFunctionAst *evaluate(Binding *b);
};
