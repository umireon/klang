#pragma once

#include "ast/AstNode.h"
#include "ast/AstArgument.h"
#include "ast/AstInvocation.h"

#include "parser/types.h"
#include "parser/BaseParse.h"
#include "parser/TokenNumber.h"
#include "parser/TokenIdentifier.h"

class ParsePrimary : public BaseParse {
public:
    BaseParse *parseExpression;
    BaseParse *parseParen;
    BaseParse *parseFunction;
    BaseParse *parseIf;
    TokenNumber *tokenNumber;
    TokenIdentifier *tokenIdentifier;

	virtual AstNode *parse(pstr_t str)
	{
		return parse_primary(str);
	}

	AstNode *parse_primary(pstr_t str);

protected:
	enum SymbolType {
		SYMBOL_FIRST_NUMBER,
		SYMBOL_ALPHABET,
		SYMBOL_PAREN_LEFT,
		SYMBOL_PAREN_RIGHT,
		SYMBOL_COMMA,
		SYMBOL_FOLLOW,
	};
    
	enum SymbolType get_symbol(pstr_t str);
    
	AstNode *parse_identifier_or_invocation(pstr_t str);
	AstInvocation *wrap_with_invocation(AstIdentifier* node, pstr_t str);
	AstArgument *parse_argument(pstr_t str);
};
