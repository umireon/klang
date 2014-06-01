#pragma once

#include "kobject/KObject.h"
#include "Binding.h"

#include "ast/AstParentNode.h"

class AstPower : public AstParentNode {
public:
	virtual KObject *evaluate(Binding *b);
};
