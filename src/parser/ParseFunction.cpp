#include <sstream>
#include <stdexcept>

#include "ast/AstFunction.h"

#include "parser/types.h"
#include "parser/ParseCompound.h"
#include "parser/ParseExpression.h"
#include "parser/ParseFunction.h"
#include "parser/ParseParameter.h"

AstFunction *ParseFunction::parse_function(pstr_t str)
{
    AstFunction *astFunc = new AstFunction();
    astFunc->strhead = str;

    AstParameter *astParam;
    ParseParameter pp;
    switch (get_symbol(str[0])) {
        case SYMBOL_PAREN_LEFT:
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
    AstNode *body;
    ParseExpression pe;
    ParseCompound pc;
    switch (get_symbol(str[0])) {
        case SYMBOL_BRACE_LEFT:
            body = pc.parse_compound(str);
            break;
        default:
            body = pe.parse_expression(str);
    }

    astFunc->body = body;
    astFunc->strtail = body->strtail;

    return astFunc;
}

pstr_t ParseFunction::scan(pstr_t str)
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
        case '{':
            return SYMBOL_BRACE_LEFT;
        default:
            return SYMBOL_FOLLOW;
    }
}
