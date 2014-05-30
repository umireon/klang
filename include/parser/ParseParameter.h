#pragma once

#include "ast/AstParameter.h"

class ParseParameter {
public:
	AstParameter *parse_parameter(const char *str);
private:
	enum SymbolType {
		SYMBOL_PAREN_LEFT,
		SYMBOL_PAREN_RIGHT,
		SYMBOL_COMMA,
		SYMBOL_FOLLOW,
		SYMBOL_WHITESPACE,
	};
    
	enum SymbolType get_symbol(char c);
	const char *scan(const char *str);

	const char *read_comma_or_follow(const char *str);
};
