#pragma once

#include "kobject/KObject.h"
#include "Binding.h"

#include "ast/AstNode.h"
#include "ast/AstIdentifier.h"
#include "ast/AstArgument.h"

class AstInvocation : public AstNode {
public:
	AstIdentifier *ident;
	AstArgument *astArgs;

    virtual ~AstInvocation();

    virtual KObject *evaluate(Binding *b);
};
