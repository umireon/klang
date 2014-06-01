#include <sstream>
#include <stdexcept>

#include "ast/AstParameter.h"

#include "parser/types.h"
#include "parser/ParseIdentifier.h"
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

    ParseIdentifier p;
    while (true) {
        str = scan(str);
        switch (get_symbol(str[0])) {
            case SYMBOL_PAREN_RIGHT:
                astParam->strtail = str + 1;
                return astParam;
            default:
                AstIdentifier *ident = p.parse_identifier(str);
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

pstr_t ParseParameter::scan(pstr_t str)
{
    enum SymbolType type;

    do {
        type = get_symbol(str[0]);
        str++;
    } while (type == SYMBOL_WHITESPACE);

    return str - 1;
}

enum ParseParameter::SymbolType ParseParameter::get_symbol(char c)
{
    switch (c) {
        case ' ':
            return SYMBOL_WHITESPACE;
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
