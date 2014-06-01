#pragma once

#include "kobject/KObject.h"
#include "Binding.h"

#include "ast/AstParentNode.h"

class AstParen : public AstParentNode {
public:
	virtual KObject *evaluate(Binding *b);
};
