#include "ast/AstNode.h"
#include "ast/AstNode/AstParentNode/AstCompare.h"
#include "ast/AstNode/AstParentNode/AstCompare/AstGreaterThanEqual.h"
#include "ast/AstNode/AstParentNode/AstCompare/AstGreaterThan.h"
#include "ast/AstNode/AstParentNode/AstCompare/AstLessThanEqual.h"
#include "ast/AstNode/AstParentNode/AstCompare/AstLessThan.h"

#include "parser/types.h"
#include "parser/ParseArithExpression.h"
#include "parser/ParseCompare.h"
#include "parser/ParsePrimary.h"

AstNode *ParseCompare::parse_compare(pstr_t str)
{
    ParseArithExpression p;
    AstNode *node = p.parse_arith_expression(str);

    str = scan(node->strtail);
    switch (get_symbol(str[0])) {
        case SYMBOL_LESS:
            switch (get_symbol(str[1])) {
                case SYMBOL_EQUAL:
                    str = scan(str+2);
                    return chain_less_than_equal(node, str);
                default:
                    str = scan(str+1);
                    return chain_less_than(node, str);
            }
        case SYMBOL_GREATER:
            switch (get_symbol(str[1])) {
                case SYMBOL_EQUAL:
                    str = scan(str+2);
                    return chain_greater_than_equal(node, str);
                default:
                    str = scan(str+1);
                    return chain_greater_than(node, str);
            }
        default:
            return node;
    }
}

AstLessThanEqual *ParseCompare::chain_less_than_equal(AstNode* root, pstr_t str)
{
    AstLessThanEqual *newRoot = new AstLessThanEqual();
    std::vector<AstNode *> &newChildren = newRoot->children;
    newRoot->strhead = root->strhead;
    newChildren.push_back(root);

    ParsePrimary p;
    AstNode *elem = p.parse_primary(str);
    newRoot->strtail = elem->strtail;
    newChildren.push_back(elem);

    return newRoot;
}

AstLessThan *ParseCompare::chain_less_than(AstNode* root, pstr_t str)
{
    AstLessThan *newRoot = new AstLessThan();
    std::vector<AstNode *> &newChildren = newRoot->children;
    newRoot->strhead = root->strhead;
    newChildren.push_back(root);

    ParsePrimary p;
    AstNode *elem = p.parse_primary(str);
    newRoot->strtail = elem->strtail;
    newChildren.push_back(elem);

    return newRoot;
}

AstGreaterThanEqual *ParseCompare::chain_greater_than_equal(AstNode* root, pstr_t str)
{
    AstGreaterThanEqual *newRoot = new AstGreaterThanEqual();
    std::vector<AstNode *> &newChildren = newRoot->children;
    newRoot->strhead = root->strhead;
    newChildren.push_back(root);

    ParsePrimary p;
    AstNode *elem = p.parse_primary(str);
    newRoot->strtail = elem->strtail;
    newChildren.push_back(elem);

    return newRoot;
}

AstGreaterThan *ParseCompare::chain_greater_than(AstNode* root, pstr_t str)
{
    AstGreaterThan *newRoot = new AstGreaterThan();
    std::vector<AstNode *> &newChildren = newRoot->children;
    newRoot->strhead = root->strhead;
    newChildren.push_back(root);

    ParsePrimary p;
    AstNode *elem = p.parse_primary(str);
    newRoot->strtail = elem->strtail;
    newChildren.push_back(elem);

    return newRoot;
}

enum ParseCompare::SymbolType ParseCompare::get_symbol(char c)
{
    switch (c) {
        case '<':
            return SYMBOL_LESS;
        case '>':
            return SYMBOL_GREATER;
        case '=':
            return SYMBOL_EQUAL;
        case ' ':
            return SYMBOL_WHITESPACE;
        default:
            return SYMBOL_FOLLOW;
    }
}

pstr_t ParseCompare::scan(pstr_t str)
{
    enum SymbolType type;

    do {
        type = get_symbol(str[0]);
        str++;
    } while (type == SYMBOL_WHITESPACE);

    return str - 1;
}
