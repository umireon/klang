#pragma once

#include "ast/AstIdentifier.h"

#include "parser/ParseIdentifier.h"

class ParseIdentifier {
public:
	AstIdentifier* parse_identifier(const char *str);
protected:
	enum SymbolType {
		SYMBOL_NUMBER,
		SYMBOL_ALPHABET_UPPER,
		SYMBOL_ALPHABET_LOWER,
		SYMBOL_FOLLOW,
	};
    
	enum SymbolType get_symbol(char c);
};
