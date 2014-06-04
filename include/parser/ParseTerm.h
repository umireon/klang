#pragma once

#include "ast/AstNode.h"
#include "ast/AstParentNode.h"
#include "ast/AstDivision.h"
#include "ast/AstMultiplication.h"
#include "ast/AstReminder.h"

#include "parser/types.h"
#include "parser/BaseParse.h"

class ParseTerm : public BaseParse {
public:
    BaseParse *parseNext;

	virtual AstNode *parse(pstr_t str)
	{
		return parse_term(str);
	}
    
	AstNode *parse_term(pstr_t str);

protected:
	enum SymbolType {
		SYMBOL_OP_ASTERISK,
		SYMBOL_OP_SLASH,
		SYMBOL_OP_PERCENT,
		SYMBOL_FOLLOW,
	};
    
	enum SymbolType get_symbol(pstr_t str);

	AstParentNode *inject_power(AstNode *root, pstr_t str);
	AstMultiplication *chain_multiplication(AstNode *root, pstr_t str);
	AstDivision *chain_division(AstNode *root, pstr_t str);
	AstReminder *chain_reminder(AstNode *root, pstr_t str);
};