#include <sstream>
#include <stdexcept>

#include "ast/AstParameter.h"

#include "parser/types.h"
#include "parser/TokenIdentifier.h"
#include "parser/ParseParameter.h"

AstParameter *ParseParameter::parse_parameter(pstr_t str)
{
    AstParameter *astParam = new AstParameter();
    astParam->strhead = str;

    str = read_paren_left(str);

    while (true) {
        str = scan(str);
        switch (get_symbol(str)) {
            case SYMBOL_PAREN_RIGHT:
                astParam->strtail = str + 1;
                return astParam;
            default:
                AstIdentifier *ident = tokenIdentifier->parse_identifier(str);
                astParam->params.push_back(ident);

                str = scan(ident->strtail);
                str = read_comma_or_follow(str);
                if (*str == '\0') {
                    astParam->strtail = str;
                    return astParam;
                }
                break;
        }
    }
}

pstr_t ParseParameter::read_paren_left(pstr_t str)
{
    switch (get_symbol(str)) {
        case SYMBOL_PAREN_LEFT:
            return str + 1;
        default:
            pstr_t recover = syntaxErrorHandler->invalid_char(str, "ParseParameter::read_paren_left");
            if (*recover != '\0') {
                return read_paren_left(recover);
            } else {
                return recover;
            }
    }
}

pstr_t ParseParameter::read_comma_or_follow(pstr_t str)
{
    switch (get_symbol(str)) {
        case SYMBOL_COMMA:
            return str + 1;
        case SYMBOL_PAREN_RIGHT:
            return str;
        default:
            pstr_t recover = syntaxErrorHandler->invalid_char(str, "ParseParameter::read_comma_or_follow");
            if (*recover != '\0') {
                return read_comma_or_follow(recover);
            } else {
                return recover;
            }
    }
}

enum ParseParameter::SymbolType ParseParameter::get_symbol(pstr_t str)
{
    switch (*str) {
        case '(':
            return SYMBOL_PAREN_LEFT;
        case ')':
            return SYMBOL_PAREN_RIGHT;
        case ',':
            return SYMBOL_COMMA;
        default:
            return SYMBOL_FOLLOW;
    }
}
