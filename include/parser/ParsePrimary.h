#pragma once

#include "ast/AstNode.h"
#include "ast/AstArgument.h"
#include "ast/AstInvocation.h"

#include "parser/types.h"

class ParsePrimary {
public:
	AstNode* parse_primary(pstr_t str);
protected:
	enum SymbolType {
		SYMBOL_FIRST_NUMBER,
		SYMBOL_ALPHABET,
		SYMBOL_PAREN_LEFT,
		SYMBOL_PAREN_RIGHT,
		SYMBOL_COMMA,
		SYMBOL_FOLLOW,
		SYMBOL_WHITESPACE,
	};
    
	enum SymbolType get_symbol(char c);
	pstr_t scan_lexical_symbol(pstr_t str);
    
	AstNode* parse_identifier_or_invocation(pstr_t str);
	AstInvocation* wrap_with_invocation(AstIdentifier* node, pstr_t str);
	AstArgument* parse_argument(pstr_t str);
};
