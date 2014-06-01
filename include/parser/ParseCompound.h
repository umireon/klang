#pragma once

#include "ast/AstCompound.h"

#include "parser/types.h"

class ParseCompound {
public:
	AstCompound *parse_compound(pstr_t str);
    
protected:
	enum SymbolType {
		SYMBOL_BRACE_LEFT,
		SYMBOL_BRACE_RIGHT,
		SYMBOL_FOLLOW,
		SYMBOL_WHITESPACE,
	};
    
	enum SymbolType get_symbol(char c) const;
	pstr_t scan(pstr_t str) const;
};
