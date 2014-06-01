#pragma once

#include "ast/AstParen.h"

#include "parser/types.h"

class ParseParen {
public:
	AstParen *parse_paren(pstr_t str);

protected:
	enum SymbolType {
		SYMBOL_PAREN_LEFT,
		SYMBOL_PAREN_RIGHT,
		SYMBOL_FOLLOW,
		SYMBOL_WHITESPACE,
	};
    
	enum SymbolType get_symbol(char c);
	pstr_t scan_lexical_symbol(pstr_t str);
};