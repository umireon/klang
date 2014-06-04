#include <vector>

#include "ast/AstParameter.h"

AstParameter::~AstParameter(void)
{
	std::vector<AstIdentifier *>::iterator iter = params.begin();

	while (iter != params.end()) {
		delete *iter;
		iter++;
	}
}
