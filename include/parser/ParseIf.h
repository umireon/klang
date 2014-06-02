#pragma once

#include "ast/AstNode.h"
#include "ast/AstIf.h"

#include "parser/types.h"
#include "parser/BaseParse.h"
#include "parser/TokenIdentifier.h"

class ParseIf : public BaseParse {
public:
    BaseParse *parseExpression;
    BaseParse *parseCompound;
    TokenIdentifier *tokenIdentifier;
    
    virtual AstNode *parse(pstr_t str)
    {
        return parse_if(str);
    }

	AstIf *parse_if(pstr_t str);

private:
	enum SymbolType {
		SYMBOL_BRACE_LEFT,
		SYMBOL_FOLLOW,
	};
    
	enum SymbolType get_symbol(pstr_t str);
};
