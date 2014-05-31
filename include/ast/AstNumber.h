#pragma once

#include "kobject.h"
#include "Binding.h"
#include "ast/AstNode.h"

class AstNumber : public AstNode {
public:
	virtual KNumber *evaluate(Binding *b) = 0;
};
