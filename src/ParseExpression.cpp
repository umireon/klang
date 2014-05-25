#include <sstream>
#include <stdexcept>

#include "ast.h"
#include "Parse.h"

AstNode* ParseExpression::parse_expression(const char *str)
{
	ParseArithExpression p;
	return p.parse_arith_expression(str);
}
