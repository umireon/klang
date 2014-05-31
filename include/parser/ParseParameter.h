#pragma once

#include "ast/AstParameter.h"

#include "parser/types.h"

class ParseParameter {
public:
	AstParameter *parse_parameter(pstr_t str);
private:
	enum SymbolType {
		SYMBOL_PAREN_LEFT,
		SYMBOL_PAREN_RIGHT,
		SYMBOL_COMMA,
		SYMBOL_FOLLOW,
		SYMBOL_WHITESPACE,
	};
    
	enum SymbolType get_symbol(char c);
	pstr_t scan(pstr_t str);

	pstr_t read_comma_or_follow(pstr_t str);
};
