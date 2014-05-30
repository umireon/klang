#include <iostream>
#include <sstream>
#include <stdexcept>

#include "ast/AstFunction.h"
#include "parser.h"
#include "parser/ParseParameter.h"
#include "parser/ParseFunction.h"

AstFunction *ParseFunction::parse_function(const char *str)
{
    AstFunction *astFunc = new AstFunction();
    astFunc->strhead = str;

    AstParameter *astParam;
    switch (get_symbol(str[0])) {
        case SYMBOL_PAREN_LEFT:
            ParseParameter pp;
            astParam = pp.parse_parameter(str);
            astFunc->astParam = astParam;
            str = astParam->strtail;
            break;
        default:
            std::ostringstream os;
            os << "Unexpected character: " << str[0] << std::endl;
            throw std::invalid_argument(os.str());
    }

    str = scan(str);
    ParseExpression pe;
    AstNode *body = pe.parse_expression(str);
    astFunc->body = body;
    astFunc->strtail = body->strtail;

    return astFunc;
}

const char* ParseFunction::scan(const char* str)
{
	enum SymbolType type;
    
	do {
		type = get_symbol(str[0]);
		str++;
	} while (type == SYMBOL_WHITESPACE);
    
	return str - 1;
}

enum ParseFunction::SymbolType ParseFunction::get_symbol(char c)
{
    switch (c) {
        case ' ':
            return SYMBOL_WHITESPACE;
        case '(':
            return SYMBOL_PAREN_LEFT;
        default:
            return SYMBOL_FOLLOW;
    }
}
