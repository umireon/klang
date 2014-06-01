#include <sstream>
#include <stdexcept>

#include "ast/AstNode.h"

#include "parser/types.h"
#include "parser/ParseAssignment.h"
#include "parser/ParseExpression.h"

AstNode* ParseExpression::parse_expression(pstr_t str)
{
    ParseAssignment p;
    return p.parse_assignment(str);
}
