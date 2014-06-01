#include <vector>

#include "kobject/KObject.h"
#include "Binding.h"

#include "ast/AstCompound.h"

KObject *AstCompound::evaluate(Binding *b)
{
	std::vector<AstNode *>::iterator iter = children.begin();
	KObject *res = NULL;

	while (iter != children.end()) {
		delete res;

		AstNode *node = *iter;
		res = node->evaluate(b);
		iter++;
	}

	return res;
}
