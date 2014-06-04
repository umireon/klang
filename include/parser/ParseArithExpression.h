#pragma once

#include "ast/AstNode.h"
#include "ast/AstAddition.h"
#include "ast/AstSubtraction.h"

#include "parser/types.h"
#include "parser/BaseParse.h"
#include "parser/ParseTerm.h"

class ParseArithExpression : public BaseParse {
public:
    BaseParse *parseNext;

	virtual AstNode *parse(pstr_t str)
	{
		return parse_arith_expression(str);
	}

	AstNode *parse_arith_expression(pstr_t str);

protected:
	enum SymbolType {
		SYMBOL_SIGN_PLUS,
		SYMBOL_SIGN_MINUS,
		SYMBOL_FOLLOW,
	};
    
	enum SymbolType get_symbol(pstr_t c);
    
	AstAddition* chain_addition(AstNode *root, pstr_t str);
	AstSubtraction* chain_subtraction(AstNode *root, pstr_t str);
};
