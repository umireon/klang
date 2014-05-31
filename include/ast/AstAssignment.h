#pragma once

#include "kobject.h"
#include "Binding.h"
#include "ast/AstParentNode.h"

class AstAssignment : public AstParentNode {
public:
	virtual KObject *evaluate(Binding *b);
};
