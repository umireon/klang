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
};

class Parse
{
public:
	enum symbol_type get_type_of_next_symbol(char c);

	int read_number_oct(const char **head);
	int read_number_hex(const char **head);
	int read_number_dec(const char **head);
	int read_number_hex_or_oct(const char **head);
	int read_number_signed(const char **head);
	int read_number_float(const char **head);

	AstNode* parse(const char *str);
	AstNode* parse_statement(const char *str);
	AstNode* parse_expression(const char *str);
	AstNode* parse_element(const char *str);
	AstNode* parse_term(const char *str);
	AstNode* parse_paren(const char *str);
	AstNode* parse_paren_left(const char *str);
	AstNode* parse_paren_right(const char *str);
	AstNode* parse_identifier(const char *str);
	AstNode* parse_number(const char *str);
};

