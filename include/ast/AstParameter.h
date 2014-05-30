#pragma once

#include <vector>

#include "ast/AstNode.h"
#include "ast/AstIdentifier.h"

class AstParameter : public AstNode {
public:
	std::vector<AstIdentifier *> params;

	virtual ~AstParameter();
};
