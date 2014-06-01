#pragma once

#include <vector>

#include "kobject/KObject.h"

#include "Binding.h"
#include "ast/AstNode.h"

class AstIf : public AstNode {
public:
	std::vector<AstNode *> cond;
	std::vector<AstNode *> body;

    virtual ~AstIf();

    virtual KObject *evaluate(Binding *b);
};
