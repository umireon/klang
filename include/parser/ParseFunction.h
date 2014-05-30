#pragma once

#include "ast/AstFunction.h"

class ParseFunction {
public:
	AstFunction *parse_function(const char *str);

protected:
	enum SymbolType {
		SYMBOL_PAREN_LEFT,
		SYMBOL_FOLLOW,
		SYMBOL_WHITESPACE,
	};
    
	enum SymbolType get_symbol(char c);
	const char *scan(const char *str);
};
