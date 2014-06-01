#include <sstream>
#include <stdexcept>

#include "ast.h"
#include "parser.h"

AstNode* ParseExpression::parse_expression(pstr_t str)
{
	ParseAssignment p;
	return p.parse_assignment(str);
}
