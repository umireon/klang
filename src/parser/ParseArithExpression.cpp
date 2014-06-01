#include <sstream>
#include <stdexcept>

#include "ast/AstNumber.h"
#include "ast/AstAddition.h"
#include "ast/AstSubtraction.h"

#include "parser/types.h"
#include "parser/ParseArithExpression.h"
#include "parser/ParseTerm.h"

AstNode* ParseArithExpression::parse_arith_expression(pstr_t str)
{
    AstNode *expr;
    pstr_t s = str;
    enum SymbolType type;

    type = get_symbol(str[0]);
    switch (type) {
        case SYMBOL_FOLLOW:
        case SYMBOL_SIGN_PLUS:
        case SYMBOL_SIGN_MINUS:
            ParseTerm p;
            expr = p.parse_term(str);
            s = expr->strtail;
            break;
        default:
            std::ostringstream os;
            os << "Unexpected character: " << s[0] << std::endl;
            throw std::invalid_argument(os.str());
    }

    while (1) {
        s = scan_lexical_symbol(s);
        type = get_symbol(s[0]);
        switch (type) {
            case SYMBOL_SIGN_PLUS:
                expr = chain_addition(expr, s+1);
                break;
            case SYMBOL_SIGN_MINUS:
                expr = chain_subtraction(expr, s+1);
                break;
            default:
                return expr;
        }

        s = expr->strtail;
    }
}


AstAddition* ParseArithExpression::chain_addition(AstNode* root, pstr_t str)
{
    AstAddition *newRoot = new AstAddition();
    newRoot->strhead = root->strhead;
    std::vector<AstNode*> &newChildren = newRoot->children;

    newChildren.push_back(root);

    str = scan_lexical_symbol(str);
    ParseTerm p;
    AstNode *term = p.parse_term(str);
    newChildren.push_back(term);

    newRoot->strtail = term->strtail;

    return newRoot;
}

AstSubtraction* ParseArithExpression::chain_subtraction(AstNode* root, pstr_t str)
{
    AstSubtraction *newRoot = new AstSubtraction();
    newRoot->strhead = root->strhead;
    std::vector<AstNode*> &newChildren = newRoot->children;

    newChildren.push_back(root);

    str = scan_lexical_symbol(str);
    ParseTerm p;
    AstNode *term = p.parse_term(str);
    newChildren.push_back(term);

    newRoot->strtail = term->strtail;

    return newRoot;
}

pstr_t ParseArithExpression::scan_lexical_symbol(pstr_t str)
{
    enum SymbolType type;

    do {
        type = get_symbol(str[0]);
        str++;
    } while (type == SYMBOL_WHITESPACE);

    return str - 1;
}

enum ParseArithExpression::SymbolType ParseArithExpression::get_symbol(char c)
{
    switch (c) {
        case ' ':
            return SYMBOL_WHITESPACE;
        case '+':
            return SYMBOL_SIGN_PLUS;
        case '-':
            return SYMBOL_SIGN_MINUS;
        default:
            return SYMBOL_FOLLOW;
    }
}
