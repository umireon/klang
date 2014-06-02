#pragma once

#include "ast/AstNode.h"

#include "parser/types.h"
#include "parser/BaseParse.h"

class ParseExpression : public BaseParse {
public:
    BaseParse *parseNext;

	virtual AstNode *parse(pstr_t str)
	{
		return parse_expression(str);
	}

	AstNode *parse_expression(pstr_t str);
};
