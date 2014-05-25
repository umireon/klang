#include <vector>
#include "ast.h"

enum symbol_type {
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
};

class Parse
{
public:
	enum symbol_type get_type_of_next_symbol(char c);

	AstNode* parse(const char *str);
	AstNode* parse_statement(const char *str);
	AstNode* parse_expression(const char *str);
	AstNode* parse_term(const char *str);
	AstNode* parse_primary(const char *str);
	AstNode* parse_paren(const char *str);
	AstNode* parse_identifier(const char *str);
	AstNode* parse_number(const char *str);
};

class ParseNumber {
public:
	AstNumber* parse_number(const char *str);
protected:
	enum symbol_type get_symbol(char c);
	AstNumber* read_number_signed(const char *str);

	AstInteger* read_number_hex_or_oct(const char *str);
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
	enum symbol_type get_symbol(char c);
	AstParentNode* parse_power_or_multiplication(const char *str);
	AstParentNode* chain_power(AstNode* root, const char *str);
	AstMultiplication* chain_multiplication(AstNode* root, const char *str);
	AstDivision* chain_division(AstNode* root, const char* str);
	AstReminder* chain_reminder(AstNode* root, const char* str);
};

class ParseExpression {
public:
	AstNode* parse_expression(const char *str);
protected:
	enum symbol_type get_symbol(char c);
	AstAddition* chain_addition(AstNode* root, const char *str);
	AstSubtraction* chain_subtraction(AstNode* root, const char* str);
};

class ParseIdentifier {
public:
	AstIdentifier* parse_identifier(const char *str);
protected:
	enum symbol_type get_symbol(char c);
};

class ParseParen {
public:
	AstParen* parse_paren(const char *str);
protected:
	enum symbol_type get_symbol(char c);
};

class ParsePrimary {
public:
	AstNode* parse_primary(const char *str);
protected:
	enum symbol_type get_symbol(char c);
};
