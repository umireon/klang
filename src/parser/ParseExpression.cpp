#include "ast/AstNode.h"

#include "parser/types.h"
#include "parser/ParseExpression.h"

AstNode *ParseExpression::parse_expression(pstr_t str)
{
    return parseNext->parse(str);
}
