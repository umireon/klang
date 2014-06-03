#include <sstream>
#include <stdexcept>

#include "ast/AstNode.h"
#include "ast/AstCompound.h"

#include "parser/types.h"
#include "parser/ParseExpression.h"
#include "parser/ParseCompound.h"

AstCompound *ParseCompound::parse_compound(pstr_t str)
{
    AstCompound *com = new AstCompound();
    com->strhead = str;

    str = read_brace_left(str);

    while (1) {
        str = scan(str);
        switch (get_symbol(str)) {
            case SYMBOL_BRACE_RIGHT:
                com->strtail = str + 1;
                return com;
            default:
                AstNode *expr = parseExpression->parse(str);
                str = expr->strtail;
                com->children.push_back(expr);
        }
    }
}

pstr_t ParseCompound::read_brace_left(pstr_t str)
{
    switch (get_symbol(str)) {
        case SYMBOL_BRACE_LEFT:
            return str+1;
        default:
            pstr_t recover = syntaxErrorHandler->invalid_char(str, "ParseCompound::read_brace_left");
            if (*recover != '\0') {
                return read_brace_left(recover);
            } else {
                return recover;
            }
    }
}

enum ParseCompound::SymbolType ParseCompound::get_symbol(pstr_t str)
{
    switch (*str) {
        case '{':
            return SYMBOL_BRACE_LEFT;
        case '}':
            return SYMBOL_BRACE_RIGHT;
        default:
            return SYMBOL_FOLLOW;
    }
}

bool ParseCompound::is_whitespace(pstr_t str) {
    switch (*str) {
        case '\n':
        case '\r':
        case ' ':
            return true;
        default:
            return false;
    }
}
