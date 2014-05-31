#pragma once

#include <vector>
#include "ast.h"
#include "parser/types.h"

class Parse
{
public:
	AstNode* parse(pstr_t str);
protected:
	enum SymbolType {
		SYMBOL_NUMBER_ZERO,
		SYMBOL_NUMBER_OCT,
		SYMBOL_NUMBER_DEC,
		SYMBOL_OP_ASTERISK,
		SYMBOL_OP_SLASH,
		SYMBOL_SIGN_PLUS,
		SYMBOL_SIGN_MINUS,
		SYMBOL_ALPHABET,
		SYMBOL_ALPHABET_X,
		SYMBOL_ALPHABET_HEXUPPER,
		SYMBOL_ALPHABET_HEXLOWER,
		SYMBOL_PAREN_LEFT,
		SYMBOL_PAREN_RIGHT,
		SYMBOL_NULL,
		SYMBOL_UNKNOWN,
		SYMBOL_EQUAL,
		SYMBOL_DOT,
		SYMBOL_FOLLOW,
		SYMBOL_OP_PERCENT,
		SYMBOL_WHITESPACE,
	};
    
	enum SymbolType get_symbol(char c);
	pstr_t scan_lexical_symbol(pstr_t str);
    
	AstNode* parse_statement(pstr_t str);
};

class ParseNumber {
public:
	AstNumber* parse_number(pstr_t str);
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
    
	AstNumber* read_number_signed(pstr_t str);
    
	AstNumber* read_number_hex_or_oct_or_float(pstr_t str);
	AstHexdecimal* read_number_hex(pstr_t str);
	AstOctal* read_number_oct(pstr_t str);
    
	AstNumber* read_number_dec_or_float(pstr_t str);
	AstDecimal* read_number_dec(pstr_t str);
	AstFloat* read_number_float(pstr_t str);
};

class ParseTerm {
public:
	AstNode* parse_term(pstr_t str);
protected:
	enum SymbolType {
		SYMBOL_OP_ASTERISK,
		SYMBOL_OP_SLASH,
		SYMBOL_OP_PERCENT,
		SYMBOL_FOLLOW,
		SYMBOL_WHITESPACE,
	};
    
	enum SymbolType get_symbol(char c);
	pstr_t scan_lexical_symbol(pstr_t str);
    
	AstParentNode* parse_power_or_multiplication(pstr_t str);
	AstParentNode* chain_power(AstNode* root, pstr_t str);
	AstMultiplication* chain_multiplication(AstNode* root, pstr_t str);
	AstDivision* chain_division(AstNode* root, pstr_t str);
	AstReminder* chain_reminder(AstNode* root, pstr_t str);
};

#include "parser/ParseExpression.h"

class ParseAssignment {
public:
	AstNode* parse_assignment(pstr_t str);
protected:
	enum SymbolType {
		SYMBOL_OP_ASTERISK,
		SYMBOL_OP_SLASH,
		SYMBOL_OP_PERCENT,
		SYMBOL_FOLLOW,
		SYMBOL_WHITESPACE,
	};
    
	enum SymbolType get_symbol(char c);
	pstr_t scan_lexical_symbol(pstr_t str);
    
	AstParentNode* chain_assignment(AstNode* root, pstr_t str);
};

class ParseArithExpression {
public:
	AstNode* parse_arith_expression(pstr_t str);
protected:
	enum SymbolType {
		SYMBOL_SIGN_PLUS,
		SYMBOL_SIGN_MINUS,
		SYMBOL_FOLLOW,
		SYMBOL_WHITESPACE,
	};
    
	enum SymbolType get_symbol(char c);
	pstr_t scan_lexical_symbol(pstr_t str);
    
	AstAddition* chain_addition(AstNode* root, pstr_t str);
	AstSubtraction* chain_subtraction(AstNode* root, pstr_t str);
};

#include "parser/ParseIdentifier.h"

class ParseParen {
public:
	AstParen* parse_paren(pstr_t str);
protected:
	enum SymbolType {
		SYMBOL_PAREN_LEFT,
		SYMBOL_PAREN_RIGHT,
		SYMBOL_FOLLOW,
		SYMBOL_WHITESPACE,
	};
    
	enum SymbolType get_symbol(char c);
	pstr_t scan_lexical_symbol(pstr_t str);
};

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
