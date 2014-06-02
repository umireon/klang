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

    switch (get_symbol(str[0])) {
        case SYMBOL_PAREN_LEFT:
            str++;
            break;
        default:
            std::ostringstream os;
            os << "Unexpected character: " << str[0] << std::endl;
            throw std::invalid_argument(os.str());
    }

    while (true) {
        str = scan(str);
        switch (get_symbol(str[0])) {
            case SYMBOL_PAREN_RIGHT:
                astParam->strtail = str + 1;
                return astParam;
            default:
                AstIdentifier *ident = tokenIdentifier->parse_identifier(str);
                astParam->params.push_back(ident);

                str = scan(ident->strtail);
                str = read_comma_or_follow(str);
                break;
        }
    }
}

pstr_t ParseParameter::read_comma_or_follow(pstr_t str)
{
    switch (get_symbol(str[0])) {
        case SYMBOL_COMMA:
            return str + 1;
        case SYMBOL_PAREN_RIGHT:
            return str;
        default:
            std::ostringstream os;
            os << "Unexpected character: " << str[0] << std::endl;
            throw std::invalid_argument(os.str());
    }
}

enum ParseParameter::SymbolType ParseParameter::get_symbol(char c)
{
    switch (c) {
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
