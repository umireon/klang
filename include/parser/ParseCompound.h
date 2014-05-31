#pragma once

#include "ast/AstFunction.h"

class ParseCompound {
public:
	AstCompound *parse_compound(const char *str);
    
protected:
	enum SymbolType {
		SYMBOL_BRACE_LEFT,
		SYMBOL_BRACE_RIGHT,
		SYMBOL_FOLLOW,
		SYMBOL_WHITESPACE,
	};
    
	enum SymbolType get_symbol(char c) const;
	const char *scan(const char *str) const;
};
