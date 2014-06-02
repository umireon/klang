#include <sstream>
#include <stdexcept>

#include "ast/AstIdentifier.h"

#include "parser/types.h"
#include "parser/TokenIdentifier.h"

AstIdentifier* TokenIdentifier::parse_identifier(pstr_t str)
{
    AstIdentifier *ident = new AstIdentifier();
    ident->strhead = str;

    switch (get_symbol(str)) {
        case SYMBOL_ALPHABET:
            str++;
            break;
        case SYMBOL_NUMBER:
        case SYMBOL_FOLLOW:
            pstr_t recover = syntaxErrorHandler->invalid_char(str);
            if (*recover != '\0') {
                return parse_identifier(syntaxErrorHandler->invalid_char(str));
            } else {
                ident->strtail = ident->strhead;
                return ident;
            }
    }

    while (1) {
        switch (get_symbol(str)) {
            case SYMBOL_ALPHABET:
            case SYMBOL_NUMBER:
                str++;
                break;
            case SYMBOL_FOLLOW:
                ident->strtail = str;
                ident->value = ident->get_string();
                return ident;
        }
    }
}

enum TokenIdentifier::SymbolType TokenIdentifier::get_symbol(pstr_t str)
{
    char c = *str;
    if ('0' <= c && c <= '9') {
        return SYMBOL_NUMBER;
    } else if (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z')) {
        return SYMBOL_ALPHABET;
    } else {
        return SYMBOL_FOLLOW;
    }
}
