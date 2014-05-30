#pragma once

#include "ast/AstNode.h"
#include "ast/AstParameter.h"
#include "kobject/KFunctionAst.h"

class AstFunction : public AstNode {
public:
	AstParameter *astParam;
	AstNode *body;
	AstIdentifier *identName;

	virtual ~AstFunction();
	virtual KFunctionAst* evaluate(Binding *b);
};
