#pragma once

#include "kobject.h"
#include "ast/AstParentNode.h"

class AstCompound : public AstParentNode {
public:
	virtual KObject *evaluate(Binding *b);
};
