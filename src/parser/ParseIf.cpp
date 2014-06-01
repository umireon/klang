#include <sstream>
#include <stdexcept>

#include "ast/AstFunction.h"
#include "ast/AstIdentifier.h"
#include "ast/AstIf.h"

#include "parser/types.h"
#include "parser/ParseCompound.h"
#include "parser/ParseExpression.h"
#include "parser/ParseIdentifier.h"
#include "parser/ParseParameter.h"
#include "parser/ParseIf.h"

AstIf *ParseIf::parse_if(pstr_t str)
{
    AstIf *astIf = new AstIf();
    astIf->strhead = str;
    
    AstNode *node;
    while (true) {
        ParseExpression pe;
        node = pe.parse_expression(str);
        str = node->strtail;
        astIf->cond.push_back(node);

        
        str = scan(str);
        ParseCompound pc;
        switch (get_symbol(str[0])) {
            case SYMBOL_BRACE_LEFT:
                node = pc.parse_compound(str);
                break;
            default:
                node = pe.parse_expression(str);
        }
        str = astIf->strtail = node->strtail;
        astIf->body.push_back(node);
        
        
        str = scan(str);
        AstIdentifier *ident;
        ParseIdentifier pi;
        
        if (str[0] != 'e') {
            return astIf;
        }

        ident = pi.parse_identifier(str);
        enum AstIdentifier::IdentifierType itype = ident->get_identifier_type();
        str = scan(ident->strtail);
        delete ident;
        
        switch (itype) {
            case AstIdentifier::ELSIF:
                continue;
            case AstIdentifier::ELSE:
                switch (get_symbol(str[0])) {
                    case SYMBOL_BRACE_LEFT:
                        node = pc.parse_compound(str);
                        break;
                    default:
                        node = pe.parse_expression(str);
                }
                str = astIf->strtail = node->strtail;
                astIf->body.push_back(node);
            default:
                return astIf;
        }
    }
}

pstr_t ParseIf::scan(pstr_t str)
{
	enum SymbolType type;
    
	do {
		type = get_symbol(str[0]);
		str++;
	} while (type == SYMBOL_WHITESPACE);
    
	return str - 1;
}

enum ParseIf::SymbolType ParseIf::get_symbol(char c)
{
    switch (c) {
        case ' ':
            return SYMBOL_WHITESPACE;
        case '{':
            return SYMBOL_BRACE_LEFT;
        default:
            return SYMBOL_FOLLOW;
    }
}
