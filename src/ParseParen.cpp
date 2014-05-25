#include <iostream>
#include <sstream>
#include <stdexcept>

#include "ast.h"
#include "Parse.h"

AstParen* ParseParen::parse_paren(const char *str)
{
	AstParen* paren = new AstParen();
	const char *s = str;
	enum symbol_type type;

	type = get_symbol(s[0]);
	switch (type) {
	case SYMBOL_PAREN_LEFT:
		s++;
		break;
	default:
        std::ostringstream os;
        os << "Unexpected character: " << s[0] << std::endl;
        throw std::invalid_argument(os.str());
	}

	ParseExpression p;
	AstNode *expr = p.parse_expression(s);
	s = expr->strtail;
	paren->children.push_back(expr);

	type = get_symbol(s[0]);
	switch (type) {
	case SYMBOL_PAREN_RIGHT:
		s++;
		break;
	default:
        std::ostringstream os;
        os << "Unexpected character: " << s[0] << std::endl;
        throw std::invalid_argument(os.str());
	}

	paren->strhead = str;
	paren->strtail = s;

	return paren;
}

enum symbol_type ParseParen::get_symbol(char c)
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
