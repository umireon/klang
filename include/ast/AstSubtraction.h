#pragma once

#include "kobject.h"
#include "Binding.h"
#include "ast/AstParentNode.h"

class AstSubtraction : public AstParentNode {
public:
	virtual KObject *evaluate(Binding *b);
};