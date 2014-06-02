#pragma once

#include "ast/AstNode.h"
#include "ast/AstParentNode.h"
#include "ast/AstNumber.h"
#include "ast/AstFloat.h"
#include "ast/AstHexdecimal.h"
#include "ast/AstOctal.h"
#include "ast/AstDecimal.h"

#include "parser/types.h"
#include "parser/BaseParse.h"

class TokenNumber : public BaseParse {
public:
    virtual AstNode *parse(pstr_t str) {
        return parse_number(str);
    }

	virtual AstNumber *parse_number(pstr_t str);

protected:
	enum SymbolType {
		SYMBOL_NUMBER_ZERO,
		SYMBOL_NUMBER_OCT,
		SYMBOL_NUMBER_DEC,
		SYMBOL_SIGN,
		SYMBOL_ALPHABET_X,
		SYMBOL_ALPHABET_HEX,
		SYMBOL_DOT,
		SYMBOL_FOLLOW,
	};
    
	enum SymbolType get_symbol(char c);
    
	AstNumber *read_number_signed(pstr_t str);
    
	AstNumber *read_number_hex_or_oct_or_float(pstr_t str);
	AstHexdecimal *read_number_hex(pstr_t str);
	AstOctal *read_number_oct(pstr_t str);
    
	AstNumber *read_number_dec_or_float(pstr_t str);
	AstDecimal *read_number_dec(pstr_t str);
	AstFloat *read_number_float(pstr_t str);
};
