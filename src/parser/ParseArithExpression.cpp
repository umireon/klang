#include "ast/AstAddition.h"
#include "ast/AstSubtraction.h"

#include "parser/types.h"
#include "parser/ParseArithExpression.h"

AstNode* ParseArithExpression::parse_arith_expression(pstr_t str)
{
    AstNode *node = parseNext->parse(str);
    str = node->strtail;

    while (1) {
        str = scan(str);
        switch (get_symbol(str)) {
            case SYMBOL_SIGN_PLUS:
                node = chain_addition(node, scan(str+1));
                break;
            case SYMBOL_SIGN_MINUS:
                node = chain_subtraction(node, scan(str+1));
                break;
            case SYMBOL_FOLLOW:
                return node;
        }

        str = node->strtail;
    }
}


AstAddition* ParseArithExpression::chain_addition(AstNode* root, pstr_t str)
{
    AstAddition *newRoot = new AstAddition();
    newRoot->strhead = root->strhead;
    std::vector<AstNode *> &newChildren = newRoot->children;

    newChildren.push_back(root);

    AstNode *term = parseNext->parse(str);
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

    AstNode *term = parseNext->parse(str);
    newChildren.push_back(term);

    newRoot->strtail = term->strtail;

    return newRoot;
}

enum ParseArithExpression::SymbolType ParseArithExpression::get_symbol(pstr_t str)
{
    if (str == line->end()) {
        return SYMBOL_FOLLOW;
    }

    switch (*str) {
        case '+':
            return SYMBOL_SIGN_PLUS;
        case '-':
            return SYMBOL_SIGN_MINUS;
        default:
            return SYMBOL_FOLLOW;
    }
}
