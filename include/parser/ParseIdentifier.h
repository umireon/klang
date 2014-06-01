#pragma once

#include "ast/AstIdentifier.h"

#include "parser/types.h"

class ParseIdentifier {
public:
	AstIdentifier *parse_identifier(pstr_t str);

protected:
	enum SymbolType {
		SYMBOL_NUMBER,
		SYMBOL_ALPHABET_UPPER,
		SYMBOL_ALPHABET_LOWER,
		SYMBOL_FOLLOW,
	};
    
	enum SymbolType get_symbol(char c);
};
