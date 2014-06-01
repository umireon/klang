#pragma once

#include "kobject/KObject.h"
#include "Binding.h"

#include "ast/AstNode/AstParentNode/AstCompare.h"

class AstGreaterThanEqual : public AstCompare {
public:
	virtual KObject *evaluate(Binding *b);
};
