#pragma once

#include "ast/AstIf.h"

class ParseIf {
public:
	AstIf *parse_if(const char *str);
private:
	enum SymbolType {
		SYMBOL_BRACE_LEFT,
		SYMBOL_COMMA,
		SYMBOL_FOLLOW,
		SYMBOL_WHITESPACE,
	};
    
	enum SymbolType get_symbol(char c);
	const char *scan(const char *str);
};
