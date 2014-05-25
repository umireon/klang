#include <iostream>
#include <sstream>
#include <stdexcept>

#include "ast.h"
#include "Parse.h"

AstNode* ParsePrimary::parse_primary(const char *str)
{
	enum SymbolType type = get_symbol(str[0]);

	switch (type) {
	case SYMBOL_FIRST_NUMBER:
		ParseNumber pn;
		return pn.parse_number(str);
		break;
	case SYMBOL_PAREN_LEFT:
		ParseParen pp;
		return pp.parse_paren(str);
		break;
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

enum ParsePrimary::SymbolType ParsePrimary::get_symbol(char c)
{
	if ('0' <= c && c <= '9') {
		return SYMBOL_FIRST_NUMBER;
    } else if ('A' <= c && c <= 'Z') {
		return SYMBOL_ALPHABET;
	} else if ('a' <= c && c <= 'z') {
		return SYMBOL_ALPHABET;
    }

    switch (c) {
    case '+':
        return SYMBOL_FIRST_NUMBER;
    case '-':
        return SYMBOL_FIRST_NUMBER;
    case '(':
    	return SYMBOL_PAREN_LEFT;
    default:
        return SYMBOL_FOLLOW;
    }
}
