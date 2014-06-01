#pragma once

#include "ast/AstNode.h"
#include "ast/AstParentNode.h"

#include "parser/types.h"

class ParseAssignment {
public:
	AstNode* parse_assignment(pstr_t str);

protected:
	enum SymbolType {
		SYMBOL_OP_ASTERISK,
		SYMBOL_OP_SLASH,
		SYMBOL_OP_PERCENT,
		SYMBOL_FOLLOW,
		SYMBOL_WHITESPACE,
	};
    
	enum SymbolType get_symbol(char c);
	pstr_t scan_lexical_symbol(pstr_t str);
    
	AstParentNode* chain_assignment(AstNode* root, pstr_t str);
};
