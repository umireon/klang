#pragma once

#include "ast/AstNode.h"
#include "ast/AstAddition.h"
#include "ast/AstSubtraction.h"

#include "parser/types.h"

class ParseArithExpression {
public:
	AstNode* parse_arith_expression(pstr_t str);

protected:
	enum SymbolType {
		SYMBOL_SIGN_PLUS,
		SYMBOL_SIGN_MINUS,
		SYMBOL_FOLLOW,
		SYMBOL_WHITESPACE,
	};
    
	enum SymbolType get_symbol(char c);
	pstr_t scan_lexical_symbol(pstr_t str);
    
	AstAddition* chain_addition(AstNode* root, pstr_t str);
	AstSubtraction* chain_subtraction(AstNode* root, pstr_t str);
};
