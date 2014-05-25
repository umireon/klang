#include <sstream>
#include <stdexcept>

#include "ast.h"
#include "Parse.h"

AstNode* ParseExpression::parse_expression(const char *str)
{
	ParseAssignment p;
	return p.parse_assignment(str);
}
