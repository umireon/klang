#include <sstream>
#include <stdexcept>

#include "ast/AstFunction.h"
#include "ast/AstIdentifier.h"
#include "ast/AstIf.h"

#include "parser/types.h"
#include "parser/ParseIf.h"

AstIf *ParseIf::parse_if(pstr_t str)
{
    AstIf *astIf = new AstIf();
    astIf->strhead = str;

    AstNode *node;
    while (true) {
        node = parseExpression->parse(str);
        str = scan(node->strtail);
        astIf->cond.push_back(node);

        switch (get_symbol(str)) {
            case SYMBOL_BRACE_LEFT:
                node = parseCompound->parse(str);
                break;
            default:
                node = parseExpression->parse(str);
        }
        str = scan(node->strtail);
        astIf->body.push_back(node);

        if (str == line->end() || *str != 'e') {
            astIf->strtail = node->strtail;
            return astIf;
        }
        
        AstIdentifier *ident = tokenIdentifier->parse_identifier(str);
        enum AstIdentifier::IdentifierType itype = ident->get_identifier_type();
        str = scan(ident->strtail);
        delete ident;

        switch (itype) {
            case AstIdentifier::ELSIF:
                continue;
            case AstIdentifier::ELSE:
                switch (get_symbol(str)) {
                    case SYMBOL_BRACE_LEFT:
                        node = parseCompound->parse(str);
                        break;
                    default:
                        node = parseExpression->parse(str);
                }
                astIf->strtail = node->strtail;
                astIf->body.push_back(node);
            default:
                return astIf;
        }
    }
}

enum ParseIf::SymbolType ParseIf::get_symbol(pstr_t str)
{
    if (str == line->end()) {
        return SYMBOL_FOLLOW;
    }

    switch (*str) {
        case '{':
            return SYMBOL_BRACE_LEFT;
        default:
            return SYMBOL_FOLLOW;
    }
}
