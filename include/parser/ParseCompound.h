#pragma once

#include "ast/AstCompound.h"

#include "parser/types.h"
#include "parser/BaseParse.h"

class ParseCompound : public BaseParse {
public:
    BaseParse *parseExpression;
    
    virtual AstNode *parse(pstr_t str)
    {
        return parse_compound(str);
    }

	AstCompound *parse_compound(pstr_t str);
    
protected:
	enum SymbolType {
		SYMBOL_BRACE_LEFT,
		SYMBOL_BRACE_RIGHT,
		SYMBOL_FOLLOW,
	};
    
	virtual bool is_whitespace(pstr_t str);
    
	pstr_t read_brace_left(pstr_t str);

	enum SymbolType get_symbol(pstr_t str);
};
