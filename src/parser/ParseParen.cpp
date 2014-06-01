#include <iostream>
#include <sstream>
#include <stdexcept>

#include "ast/AstNode.h"
#include "ast/AstParen.h"

#include "parser/types.h"
#include "parser/ParseExpression.h"
#include "parser/ParseParen.h"

AstParen* ParseParen::parse_paren(pstr_t str)
{
	AstParen* paren = new AstParen();
	pstr_t s = str;
    
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

pstr_t ParseParen::scan_lexical_symbol(pstr_t str)
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
