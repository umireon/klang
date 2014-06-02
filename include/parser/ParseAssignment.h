#pragma once

#include "ast/AstNode.h"
#include "ast/AstParentNode.h"

#include "parser/types.h"
#include "parser/BaseParse.h"

class ParseAssignment : public BaseParse {
public:
    BaseParse *parseNext;

	virtual AstNode *parse(pstr_t str)
	{
		return parse_assignment(str);
	}

	AstNode *parse_assignment(pstr_t str);

protected:
	enum SymbolType {
		SYMBOL_EQUAL,
		SYMBOL_FOLLOW,
	};
    
	enum SymbolType get_symbol(pstr_t str);
    
	AstParentNode *inject_assignment(AstNode *node, pstr_t str);
};
