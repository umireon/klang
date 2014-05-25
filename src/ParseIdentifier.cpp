#include "ast.h"
#include "parser.h"

AstIdentifier* ParseIdentifier::parse_identifier(const char *str)
{
	AstIdentifier *ident = new AstIdentifier();
	ident->strhead = str;

	enum symbol_type type;

	while (1) {
		type = get_symbol(str[0]);

		switch (type) {
		case SYMBOL_ALPHABET_HEXUPPER:
		case SYMBOL_ALPHABET_HEXLOWER:
		case SYMBOL_ALPHABET_X:
		case SYMBOL_ALPHABET:
		case SYMBOL_NUMBER_ZERO:
		case SYMBOL_NUMBER_OCT:
		case SYMBOL_NUMBER_DEC:
			str++;
			break;
		default:
			ident->strtail = str;
			return ident;
		}
	}
}

enum symbol_type ParseIdentifier::get_symbol(char c)
{
	char dc = c | 0x20;

	if (c == '0') {
		return SYMBOL_NUMBER_ZERO;
	} else if ('1' <= c && c <= '7') {
		return SYMBOL_NUMBER_OCT;
	} else if (c == '8' || c == '9') {
		return SYMBOL_NUMBER_DEC;
	} else if ('A' <= c && c <= 'F') {
		return SYMBOL_ALPHABET_HEXUPPER;
	} else if ('a' <= c && c <= 'f') {
		return SYMBOL_ALPHABET_HEXLOWER;
	} else if (dc == 'x') {
		return SYMBOL_ALPHABET_X;
	} else if ('g' <= dc && dc <= 'z') {
		return SYMBOL_ALPHABET;
	} else if (c == '*') {
		return SYMBOL_OP_ASTERISK;
	} else if (c == '/') {
		return SYMBOL_OP_SLASH;
	} else if (c == '%') {
		return SYMBOL_OP_PERCENT;
	} else if (c == '+') {
		return SYMBOL_SIGN_PLUS;
	} else if (c == '+') {
		return SYMBOL_SIGN_PLUS;
	} else if (c == '-') {
		return SYMBOL_SIGN_MINUS;
	} else if (c == '(') {
		return SYMBOL_PAREN_LEFT;
	} else if (c == ')') {
		return SYMBOL_PAREN_RIGHT;
	} else if (c == '.') {
		return SYMBOL_DOT;
	} else if (c == '\0') {
		return SYMBOL_NULL;
	} else {
		return SYMBOL_UNKNOWN;
	}
}
