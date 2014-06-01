#pragma once

#include "ast/AstIf.h"

#include "parser/types.h"

class ParseIf {
public:
	AstIf *parse_if(pstr_t str);

private:
	enum SymbolType {
		SYMBOL_BRACE_LEFT,
		SYMBOL_COMMA,
		SYMBOL_FOLLOW,
		SYMBOL_WHITESPACE,
	};
    
	enum SymbolType get_symbol(char c);
	pstr_t scan(pstr_t str);
};
