#include "ast/AstFunction.h"
#include "ast/AstParameter.h"

#include "parser/types.h"
#include "parser/ParseFunction.h"
#include "parser/ParseParameter.h"

AstFunction *ParseFunction::parse_function(pstr_t str)
{
    AstFunction *astFunc = new AstFunction();
    astFunc->strhead = str;

    str = check_paren_left(str);
    AstParameter *astParam = parseParameter->parse_parameter(str);
    astFunc->astParam = astParam;
    str = scan(astParam->strtail);

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

pstr_t ParseFunction::check_paren_left(pstr_t str)
{
    switch (get_symbol(str)) {
        case SYMBOL_PAREN_LEFT:
            return str;
        default:
            pstr_t recover = syntaxErrorHandler->invalid_char(str, "ParseFunction::check_paren_left");
            if (*recover != '\0') {
                return check_paren_left(recover);
            } else {
                return recover;
            }
    }
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
