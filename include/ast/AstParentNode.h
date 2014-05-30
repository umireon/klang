#pragma once

#include "Binding.h"

#include "ast/AstNode.h"

class AstParentNode : public AstNode {
public:
	std::vector<AstNode*> children;
    
    virtual ~AstParentNode();
	virtual int size() { return children.size(); }
};