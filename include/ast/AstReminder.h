#pragma once

#include "kobject.h"
#include "Binding.h"
#include "ast/AstParentNode.h"

class AstReminder : public AstParentNode {
public:
	virtual KObject *evaluate(Binding *b);
};
