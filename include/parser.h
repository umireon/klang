#pragma once

#include <vector>
#include "ast.h"

class Parse
{
public:
	AstNode* parse(const char *str);
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
	const char* scan_lexical_symbol(const char* str);
    
	AstNode* parse_statement(const char *str);
};

class ParseNumber {
public:
	AstNumber* parse_number(const char *str);
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
    
	AstNumber* read_number_signed(const char *str);
    
	AstNumber* read_number_hex_or_oct_or_float(const char *str);
	AstHexdecimal* read_number_hex(const char *str);
	AstOctal* read_number_oct(const char *str);
    
	AstNumber* read_number_dec_or_float(const char *str);
	AstDecimal* read_number_dec(const char *str);
	AstFloat* read_number_float(const char *str);
};

class ParseTerm {
public:
	AstNode* parse_term(const char *str);
protected:
	enum SymbolType {
		SYMBOL_OP_ASTERISK,
		SYMBOL_OP_SLASH,
		SYMBOL_OP_PERCENT,
		SYMBOL_FOLLOW,
		SYMBOL_WHITESPACE,
	};
    
	enum SymbolType get_symbol(char c);
	const char* scan_lexical_symbol(const char* str);
    
	AstParentNode* parse_power_or_multiplication(const char *str);
	AstParentNode* chain_power(AstNode* root, const char *str);
	AstMultiplication* chain_multiplication(AstNode* root, const char *str);
	AstDivision* chain_division(AstNode* root, const char* str);
	AstReminder* chain_reminder(AstNode* root, const char* str);
};

class ParseExpression {
public:
	AstNode* parse_expression(const char *str);
};

class ParseAssignment {
public:
	AstNode* parse_assignment(const char *str);
protected:
	enum SymbolType {
		SYMBOL_OP_ASTERISK,
		SYMBOL_OP_SLASH,
		SYMBOL_OP_PERCENT,
		SYMBOL_FOLLOW,
		SYMBOL_WHITESPACE,
	};
    
	enum SymbolType get_symbol(char c);
	const char* scan_lexical_symbol(const char* str);
    
	AstParentNode* chain_assignment(AstNode* root, const char *str);
};

class ParseArithExpression {
public:
	AstNode* parse_arith_expression(const char *str);
protected:
	enum SymbolType {
		SYMBOL_SIGN_PLUS,
		SYMBOL_SIGN_MINUS,
		SYMBOL_FOLLOW,
		SYMBOL_WHITESPACE,
	};
    
	enum SymbolType get_symbol(char c);
	const char* scan_lexical_symbol(const char* str);
    
	AstAddition* chain_addition(AstNode* root, const char *str);
	AstSubtraction* chain_subtraction(AstNode* root, const char* str);
};

class ParseIdentifier {
public:
	AstIdentifier* parse_identifier(const char *str);
protected:
	enum SymbolType {
		SYMBOL_NUMBER,
		SYMBOL_ALPHABET_UPPER,
		SYMBOL_ALPHABET_LOWER,
		SYMBOL_FOLLOW,
	};
    
	enum SymbolType get_symbol(char c);
};

class ParseParen {
public:
	AstParen* parse_paren(const char *str);
protected:
	enum SymbolType {
		SYMBOL_PAREN_LEFT,
		SYMBOL_PAREN_RIGHT,
		SYMBOL_FOLLOW,
		SYMBOL_WHITESPACE,
	};
    
	enum SymbolType get_symbol(char c);
	const char* scan_lexical_symbol(const char* str);
};

class ParsePrimary {
public:
	AstNode* parse_primary(const char *str);
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
	const char* scan_lexical_symbol(const char* str);
    
	AstNode* parse_identifier_or_invocation(const char *str);
	AstInvocation* wrap_with_invocation(AstIdentifier* node, const char *str);
	AstArgument* parse_argument(const char *str);
};
