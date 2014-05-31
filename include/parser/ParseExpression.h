#pragma once

#include "ast/AstNode.h"

#include "parser/types.h"

class ParseExpression {
public:
	AstNode* parse_expression(pstr_t str);
};
