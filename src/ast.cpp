#include <stdlib.h>
#include <sstream>
#include "ast.h"

AstNode::~AstNode(void)
{
	int size = children.size();
	for (int i = 0; i < size; i++) {
		delete children.at(i);
	}
}


long AstInteger::get_long()
{
	std::string s(strhead, strtail - strhead);
	return strtol(s.c_str(), NULL, 0);
}

double AstInteger::get_double()
{
	return get_long();
}


long AstFloat::get_long()
{
	return get_double();
}

double AstFloat::get_double()
{
	std::string s(strhead, strtail - strhead);
	return strtod(s.c_str(), NULL);
}
