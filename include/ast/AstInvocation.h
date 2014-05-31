#pragma once

#include "kobject.h"
#include "Binding.h"
#include "ast/AstNode.h"

class AstInvocation : public AstNode {
public:
	AstIdentifier *ident;
	AstArgument *astArgs;

    virtual ~AstInvocation();

    virtual KObject *evaluate(Binding *b);
};
