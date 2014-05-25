#include <stdlib.h>
#include <sstream>
#include "ast.h"

std::string AstNode::get_string() {
    return std::string(strhead, strtail - strhead);
}

AstParentNode::~AstParentNode(void)
{
	int size = children.size();
	for (int i = 0; i < size; i++) {
		delete children.at(i);
	}
}

long AstParen::get_long()
{
	return children.at(0)->get_long();
}

long AstInteger::get_long()
{
	return strtol(get_string().c_str(), NULL, 0);
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
	return strtod(get_string().c_str(), NULL);
}
