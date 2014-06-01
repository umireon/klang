#pragma once

#include "kobject/KObject.h"
#include "ast/AstParentNode.h"

class AstCompound : public AstParentNode {
public:
	virtual KObject *evaluate(Binding *b);
};
