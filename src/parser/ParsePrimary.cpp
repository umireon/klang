#include <sstream>
#include <stdexcept>

#include "ast/AstNode.h"
#include "ast/AstArgument.h"
#include "ast/AstIdentifier.h"
#include "ast/AstInvocation.h"

#include "parser/types.h"
#include "parser/ParseExpression.h"
#include "parser/ParseFunction.h"
#include "parser/ParseIdentifier.h"
#include "parser/ParseIf.h"
#include "parser/ParseNumber.h"
#include "parser/ParseParameter.h"
#include "parser/ParseParen.h"
#include "parser/ParsePrimary.h"

AstNode* ParsePrimary::parse_primary(pstr_t str)
{
    switch (get_symbol(str)) {
        case SYMBOL_FIRST_NUMBER:
            ParseNumber pn;
            return pn.parse_number(str);
            break;
        case SYMBOL_PAREN_LEFT:
            return parseParen->parse(str);
            break;
        case SYMBOL_ALPHABET:
            return parse_identifier_or_invocation(str);
            break;
        default:
            std::ostringstream os;
            os << "Unexpected character: " << str[0] << std::endl;
            throw std::invalid_argument(os.str());
    }
}

AstNode* ParsePrimary::parse_identifier_or_invocation(pstr_t str)
{
    ParseIdentifier pi;
    ParseIf pif;
    AstIdentifier *ident = pi.parse_identifier(str);

    str = ident->strtail;
    str = scan(str);
    switch (ident->get_identifier_type()) {
        case AstIdentifier::FUNCTION:
            delete ident;
            return parseFunction->parse(scan(str));
        case AstIdentifier::IF:
            delete ident;
            return parseIf->parse(scan(str));
        case AstIdentifier::NAME:
            switch (get_symbol(str)) {
                case SYMBOL_PAREN_LEFT:
                    return wrap_with_invocation(ident, scan(str+1));
                    break;
                default:
                    return ident;
            }
            break;
        default:
            std::ostringstream os;
            os << "Unexpected identifier: " << ident->get_name() << std::endl;
            throw std::invalid_argument(os.str());
    }
}

AstInvocation* ParsePrimary::wrap_with_invocation(AstIdentifier* node, pstr_t str)
{
    AstInvocation *newRoot = new AstInvocation();
    newRoot->strhead = node->strhead;
    newRoot->ident = node;

    AstArgument *args;
    enum SymbolType type = get_symbol(str);
    switch (type) {
        case SYMBOL_PAREN_RIGHT:
            args = new AstArgument();
            args->strhead = args->strtail = newRoot->strtail = str + 1;
            newRoot->astArgs = args;
            return newRoot;
        default:
            args = parse_argument(str);
            newRoot->astArgs = args;
            str = args->strtail;
    }

    type = get_symbol(str);
    switch (type) {
        case SYMBOL_PAREN_RIGHT:
            newRoot->strtail = str + 1;
            return newRoot;
        default:
            std::ostringstream os;
            os << "Unexpected character: " << str[0] << std::endl;
            throw std::invalid_argument(os.str());
    }
}

AstArgument* ParsePrimary::parse_argument(pstr_t str)
{
    AstArgument *inv = new AstArgument();
    inv->strhead = str;

    AstNode *expr = parseExpression->parse(str);
    inv->children.push_back(expr);
    str = expr->strtail;

    while (true) {
        str = scan(str);
        enum SymbolType type = get_symbol(str);
        switch (type) {
            case SYMBOL_COMMA:
                str++;
                str = scan(str);
                expr = parseExpression->parse(str);
                inv->children.push_back(expr);
                str = expr->strtail;
                break;
            default:
                inv->strtail = str;
                return inv;
        }
    }
}

enum ParsePrimary::SymbolType ParsePrimary::get_symbol(pstr_t str)
{
    char c = *str;
    if ('0' <= c && c <= '9') {
        return SYMBOL_FIRST_NUMBER;
    } else if ('A' <= c && c <= 'Z') {
        return SYMBOL_ALPHABET;
    } else if ('a' <= c && c <= 'z') {
        return SYMBOL_ALPHABET;
    }

    switch (c) {
        case '+':
            return SYMBOL_FIRST_NUMBER;
        case '-':
            return SYMBOL_FIRST_NUMBER;
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
