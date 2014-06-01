#pragma once

#include "ast/AstNode.h"

#include "parser/types.h"

class Parse
{
public:
	AstNode *parse(pstr_t str);
protected:
	enum SymbolType {
		SYMBOL_NUMBER_ZERO,
		SYMBOL_NUMBER_OCT,
		SYMBOL_NUMBER_DEC,
		SYMBOL_OP_ASTERISK,
		SYMBOL_OP_SLASH,
		SYMBOL_SIGN_PLUS,
		SYMBOL_SIGN_MINUS,
		SYMBOL_ALPHABET,
		SYMBOL_ALPHABET_X,
		SYMBOL_ALPHABET_HEXUPPER,
		SYMBOL_ALPHABET_HEXLOWER,
		SYMBOL_PAREN_LEFT,
		SYMBOL_PAREN_RIGHT,
		SYMBOL_NULL,
		SYMBOL_UNKNOWN,
		SYMBOL_EQUAL,
		SYMBOL_DOT,
		SYMBOL_FOLLOW,
		SYMBOL_OP_PERCENT,
		SYMBOL_WHITESPACE,
	};
    
	enum SymbolType get_symbol(char c);
	pstr_t scan_lexical_symbol(pstr_t str);
    
	AstNode *parse_statement(pstr_t str);
};
