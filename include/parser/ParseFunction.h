#pragma once

#include "ast/AstFunction.h"

#include "parser/types.h"
#include "parser/BaseParse.h"

class ParseFunction : public BaseParse {
public:
    BaseParse *parseExpression;
    BaseParse *parseCompound;
    
    virtual AstNode *parse(pstr_t str)
    {
        return parse_function(str);
    }

	AstFunction *parse_function(pstr_t str);

protected:
	enum SymbolType {
		SYMBOL_PAREN_LEFT,
		SYMBOL_BRACE_LEFT,
		SYMBOL_FOLLOW,
	};
    
	enum SymbolType get_symbol(pstr_t str);
};
