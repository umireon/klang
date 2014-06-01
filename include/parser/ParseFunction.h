#pragma once

#include "ast/AstFunction.h"

#include "parser/types.h"

class ParseFunction {
public:
	AstFunction *parse_function(pstr_t str);

protected:
	enum SymbolType {
		SYMBOL_PAREN_LEFT,
		SYMBOL_BRACE_LEFT,
		SYMBOL_FOLLOW,
		SYMBOL_WHITESPACE,
	};
    
	enum SymbolType get_symbol(char c);
	pstr_t scan(pstr_t str);
};
