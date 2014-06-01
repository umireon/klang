#include "ast/AstParentNode.h"

AstParentNode::~AstParentNode(void)
{
	int size = children.size();
	for (int i = 0; i < size; i++) {
		delete children.at(i);
	}
}
