#pragma once

#include "ast/AstParen.h"

#include "parser/types.h"
#include "parser/BaseParse.h"

class ParseParen : public BaseParse {
public:
    BaseParse *parseExpression;
    
    virtual AstNode *parse(pstr_t str)
    {
        return parse_paren(str);
    }
    
	AstParen *parse_paren(pstr_t str);

protected:
	enum SymbolType {
		SYMBOL_PAREN_LEFT,
		SYMBOL_PAREN_RIGHT,
		SYMBOL_FOLLOW,
	};
    
	enum SymbolType get_symbol(pstr_t str);
};