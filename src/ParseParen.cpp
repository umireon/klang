#include <iostream>
#include <sstream>
#include <stdexcept>

#include "ast.h"
#include "Parse.h"

AstParen* ParseParen::parse_paren(const char *str)
{
	AstParen* paren = new AstParen();
	const char *s = str;

	enum SymbolType type = get_symbol(s[0]);
	switch (type) {
	case SYMBOL_PAREN_LEFT:
		s++;
		break;
	default:
        std::ostringstream os;
        os << "Unexpected character: " << s[0] << std::endl;
        throw std::invalid_argument(os.str());
	}

	s = scan_lexical_symbol(s);
	ParseExpression p;
	AstNode *expr = p.parse_expression(s);
	s = expr->strtail;
	paren->children.push_back(expr);

	s = scan_lexical_symbol(s);
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

const char* ParseParen::scan_lexical_symbol(const char* str)
{
	enum SymbolType type;

	do {
		type = get_symbol(str[0]);
		str++;
	} while (type == SYMBOL_WHITESPACE);

	return str - 1;
}

enum ParseParen::SymbolType ParseParen::get_symbol(char c)
{
	switch (c) {
	case ' ':
		return SYMBOL_WHITESPACE;
	case '(':
		return SYMBOL_PAREN_LEFT;
	case ')':
		return SYMBOL_PAREN_RIGHT;
	default:
		return SYMBOL_FOLLOW;
	}
}
