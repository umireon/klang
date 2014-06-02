#pragma once

#include "ast/AstParameter.h"

#include "parser/types.h"
#include "parser/BaseParse.h"
#include "parser/TokenIdentifier.h"

class ParseParameter : public BaseParse {
public:
    TokenIdentifier *tokenIdentifier;
    
    virtual AstNode *parse(pstr_t str)
    {
        return parse_parameter(str);
    }

	virtual AstParameter *parse_parameter(pstr_t str);

private:
	enum SymbolType {
		SYMBOL_PAREN_LEFT,
		SYMBOL_PAREN_RIGHT,
		SYMBOL_COMMA,
		SYMBOL_FOLLOW,
		SYMBOL_WHITESPACE,
	};
    
	enum SymbolType get_symbol(char c);
	pstr_t read_comma_or_follow(pstr_t str);
};
