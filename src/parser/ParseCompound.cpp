#include <sstream>
#include <stdexcept>

#include "ast/AstNode.h"
#include "ast/AstCompound.h"
#include "parser/ParseExpression.h"
#include "parser/ParseCompound.h"

AstCompound* ParseCompound::parse_compound(const char *str)
{
	AstCompound *com = new AstCompound();
	com->strhead = str;
    
	switch (get_symbol(str[0])) {
        case SYMBOL_BRACE_LEFT:
        	str++;
            break;
        default:
            std::ostringstream os;
            os << "Unexpected character: " << str[0] << std::endl;
            throw std::invalid_argument(os.str());
	}
    
	ParseExpression p;
	AstNode *expr;
	while (1) {
		str = scan(str);
		switch (get_symbol(str[0])) {
	        case SYMBOL_BRACE_RIGHT:
	        	com->strtail = str + 1;
	        	return com;
	        default:
	        	expr = p.parse_expression(str);
	        	str = expr->strtail;
	        	com->children.push_back(expr);
		}
	}
}

enum ParseCompound::SymbolType ParseCompound::get_symbol(char c) const
{
	switch (c) {
        case '\n':
        case '\r':
        case ' ':
            return SYMBOL_WHITESPACE;
        case '{':
            return SYMBOL_BRACE_LEFT;
        case '}':
            return SYMBOL_BRACE_RIGHT;
        default:
            return SYMBOL_FOLLOW;
	}
}

const char* ParseCompound::scan(const char* str) const
{
	enum SymbolType type;
    
	do {
		type = get_symbol(str[0]);
		str++;
	} while (type == SYMBOL_WHITESPACE);
    
	return str - 1;
}
