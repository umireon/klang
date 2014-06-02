#include <sstream>
#include <stdexcept>

#include "ast/AstFunction.h"
#include "ast/AstParameter.h"

#include "parser/types.h"
#include "parser/ParseFunction.h"
#include "parser/ParseParameter.h"

AstFunction *ParseFunction::parse_function(pstr_t str)
{
    AstFunction *astFunc = new AstFunction();
    astFunc->strhead = str;

    AstParameter *astParam;
    ParseParameter pp;
    switch (get_symbol(str)) {
        case SYMBOL_PAREN_LEFT:
            astParam = pp.parse_parameter(str);
            astFunc->astParam = astParam;
            str = scan(astParam->strtail);
            break;
        default:
            std::ostringstream os;
            os << "Unexpected character: " << str[0] << std::endl;
            throw std::invalid_argument(os.str());
    }

    AstNode *body;
    switch (get_symbol(str)) {
        case SYMBOL_BRACE_LEFT:
            body = parseCompound->parse(str);
            break;
        case SYMBOL_FOLLOW:
        case SYMBOL_PAREN_LEFT:
            body = parseExpression->parse(str);
    }

    astFunc->body = body;
    astFunc->strtail = body->strtail;

    return astFunc;
}

enum ParseFunction::SymbolType ParseFunction::get_symbol(pstr_t str)
{
    switch (*str) {
        case '(':
            return SYMBOL_PAREN_LEFT;
        case '{':
            return SYMBOL_BRACE_LEFT;
        default:
            return SYMBOL_FOLLOW;
    }
}
