#pragma once

#include "kobject.h"
#include "Binding.h"
#include "ast/AstParentNode.h"

class AstMultiplication : public AstParentNode {
public:
	virtual KObject *evaluate(Binding *b);
};
