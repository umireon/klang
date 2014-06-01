#pragma once

#include "ast/AstNode.h"
#include "ast/AstParentNode.h"
#include "ast/AstDivision.h"
#include "ast/AstMultiplication.h"
#include "ast/AstReminder.h"

#include "parser/types.h"

class ParseTerm {
public:
	AstNode *parse_term(pstr_t str);
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
    
	AstParentNode *parse_power_or_multiplication(pstr_t str);
	AstParentNode *chain_power(AstNode *root, pstr_t str);
	AstMultiplication *chain_multiplication(AstNode *root, pstr_t str);
	AstDivision *chain_division(AstNode *root, pstr_t str);
	AstReminder *chain_reminder(AstNode *root, pstr_t str);
};