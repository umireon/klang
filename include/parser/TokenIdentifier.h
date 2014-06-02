#pragma once

#include "ast/AstIdentifier.h"

#include "parser/types.h"
#include "parser/BaseParse.h"

class TokenIdentifier {
public:
	virtual AstIdentifier *parse_identifier(pstr_t str);

protected:
	enum SymbolType {
		SYMBOL_NUMBER,
		SYMBOL_ALPHABET,
		SYMBOL_FOLLOW,
	};
    
	enum SymbolType get_symbol(pstr_t str);
};
