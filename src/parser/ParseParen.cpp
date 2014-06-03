#include <sstream>
#include <stdexcept>

#include "ast/AstNode.h"
#include "ast/AstParen.h"

#include "parser/types.h"
#include "parser/ParseExpression.h"
#include "parser/ParseParen.h"

AstParen* ParseParen::parse_paren(pstr_t str)
{
    AstParen* paren = new AstParen();
    paren->strhead = str;

    switch (get_symbol(str)) {
        case SYMBOL_PAREN_LEFT:
            break;
        default:
            pstr_t recover = syntaxErrorHandler->never_reach(str, __FUNCTION__);
            if (*recover != '\0') {
                delete paren;
                return parse_paren(recover);
            } else {
                paren->strtail = recover;
                return paren;
            }
    }

    AstNode *expr = parseExpression->parse(scan(str+1));
    str = scan(expr->strtail);
    paren->children.push_back(expr);

    while (true) {
        switch (get_symbol(str)) {
            case SYMBOL_PAREN_RIGHT:
                paren->strtail = str + 1;
                return paren;
            default:
                str = syntaxErrorHandler->invalid_char(str, __FUNCTION__);
                if (*str == '\0') {
                    paren->strtail = str;
                    return paren;
                }
        }
    }

}

enum ParseParen::SymbolType ParseParen::get_symbol(pstr_t str)
{
    switch (*str) {
        case '(':
            return SYMBOL_PAREN_LEFT;
        case ')':
            return SYMBOL_PAREN_RIGHT;
        default:
            return SYMBOL_FOLLOW;
    }
}
