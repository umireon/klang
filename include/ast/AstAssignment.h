#pragma once

#include "kobject/KObject.h"
#include "Binding.h"
#include "ast/AstParentNode.h"

class AstAssignment : public AstParentNode {
public:
	virtual KObject *evaluate(Binding *b);
};
