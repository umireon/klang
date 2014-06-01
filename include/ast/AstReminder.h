#pragma once

#include "kobject/KObject.h"
#include "Binding.h"

#include "ast/AstParentNode.h"

class AstReminder : public AstParentNode {
public:
	virtual KObject *evaluate(Binding *b);
};
