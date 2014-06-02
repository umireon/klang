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
            std::ostringstream os;
            os << "Unexpected character: " << str[0] << std::endl;
            throw std::invalid_argument(os.str());
    }

    AstNode *expr = parseExpression->parse(scan(str+1));
    str = scan(expr->strtail);
    paren->children.push_back(expr);

    switch (get_symbol(str)) {
        case SYMBOL_PAREN_RIGHT:
            break;
        default:
            std::ostringstream os;
            os << "Unexpected character: " << str[0] << std::endl;
            throw std::invalid_argument(os.str());
    }

    paren->strtail = str + 1;

    return paren;
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
