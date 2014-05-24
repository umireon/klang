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
	return std::strtol(s.c_str(), NULL, 0);
}


long AstOctal::get_long()
{
	std::string s(strhead, strtail - strhead);
	return std::strtol(s.c_str(), NULL, 0);
}
