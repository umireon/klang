#include <iostream>
#include <sstream>
#include <stdexcept>

#include "ast.h"
#include "parser.h"

AstNode* ParsePrimary::parse_primary(const char *str)
{
	enum symbol_type type = get_symbol(str[0]);

	switch (type) {
	case SYMBOL_NUMBER_ZERO:
	case SYMBOL_NUMBER_OCT:
	case SYMBOL_NUMBER_DEC:
	case SYMBOL_SIGN_MINUS:
	case SYMBOL_SIGN_PLUS:
		ParseNumber pn;
		return pn.parse_number(str);
		break;
	case SYMBOL_PAREN_LEFT:
		ParseParen pp;
		return pp.parse_paren(str);
		break;
	case SYMBOL_ALPHABET_HEXUPPER:
	case SYMBOL_ALPHABET_HEXLOWER:
	case SYMBOL_ALPHABET_X:
	case SYMBOL_ALPHABET:
		ParseIdentifier pi;
		return pi.parse_identifier(str);
		break;
	default:
        std::ostringstream os;
        os << "Unexpected character: " << str[0] << std::endl;
        throw std::invalid_argument(os.str());
	}
}


enum symbol_type ParsePrimary::get_symbol(char c)
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
