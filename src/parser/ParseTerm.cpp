#include "ast/AstNode.h"
#include "ast/AstParentNode.h"
#include "ast/AstDivision.h"
#include "ast/AstMultiplication.h"
#include "ast/AstPower.h"
#include "ast/AstReminder.h"

#include "parser/types.h"
#include "parser/ParseTerm.h"

AstNode *ParseTerm::parse_term(pstr_t str)
{
    AstNode *term = parseNext->parse(str);
    str = term->strtail;

    while (1) {
        str = scan(str);
        switch (get_symbol(str)) {
            case SYMBOL_OP_ASTERISK:
                switch (get_symbol(str+1)) {
                    case SYMBOL_OP_ASTERISK:
                        term = inject_power(term, scan(str+2));
                        break;
                    default:
                        term = chain_multiplication(term, scan(str+1));
                        break;
                }
                break;
            case SYMBOL_OP_SLASH:
                term = chain_division(term, scan(str+1));
                break;
            case SYMBOL_OP_PERCENT:
                term = chain_reminder(term, scan(str+1));
                break;
            default:
                return term;
        }

        str = term->strtail;
    }
}

AstParentNode *ParseTerm::inject_power(AstNode *node, pstr_t str)
{
    if (node->size() == 2) {
        AstParentNode *root = static_cast<AstParentNode *>(node);
        root->children[1] = inject_power(root->children[1], str);
        node->strtail = root->children[1]->strtail;
        return root;
    } else {
        AstPower *newRoot = new AstPower();
        newRoot->strhead = node->strhead;
        std::vector<AstNode *> &newChildren = newRoot->children;

        newChildren.push_back(node);

        str = scan(str);
        AstNode *elem = parseNext->parse(str);
        newChildren.push_back(elem);

        newRoot->strtail = elem->strtail;

        return newRoot;
    }
}

AstMultiplication *ParseTerm::chain_multiplication(AstNode *root, pstr_t str)
{
    AstMultiplication *newRoot = new AstMultiplication();
    newRoot->strhead = root->strhead;
    std::vector<AstNode *> &newChildren = newRoot->children;

    newChildren.push_back(root);

    str = scan(str);
    AstNode *elem = parseNext->parse(str);
    newChildren.push_back(elem);

    newRoot->strtail = elem->strtail;

    return newRoot;
}

AstDivision *ParseTerm::chain_division(AstNode *root, pstr_t str)
{
    AstDivision *newRoot = new AstDivision();
    newRoot->strhead = root->strhead;
    std::vector<AstNode *> &newChildren = newRoot->children;

    newChildren.push_back(root);

    str = scan(str);
    AstNode *elem = parseNext->parse(str);
    newChildren.push_back(elem);

    newRoot->strtail = elem->strtail;

    return newRoot;
}

AstReminder *ParseTerm::chain_reminder(AstNode *root, pstr_t str)
{
    AstReminder *newRoot = new AstReminder();
    newRoot->strhead = root->strhead;
    std::vector<AstNode *> &newChildren = newRoot->children;

    newChildren.push_back(root);

    str = scan(str);
    AstNode *elem = parseNext->parse(str);
    newChildren.push_back(elem);

    newRoot->strtail = elem->strtail;

    return newRoot;
}

enum ParseTerm::SymbolType ParseTerm::get_symbol(pstr_t str)
{
    if (str == line->end()) {
        return SYMBOL_FOLLOW;
    }

    switch (*str) {
        case '*':
            return SYMBOL_OP_ASTERISK;
        case '/':
            return SYMBOL_OP_SLASH;
        case '%':
            return SYMBOL_OP_PERCENT;
        default:
            return SYMBOL_FOLLOW;
    }
}
