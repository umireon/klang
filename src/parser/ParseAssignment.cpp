#include <sstream>
#include <stdexcept>

#include "ast/AstNode.h"
#include "ast/AstParentNode.h"
#include "ast/AstAssignment.h"

#include "parser/types.h"
#include "parser/BaseParse.h"
#include "parser/ParseAssignment.h"

AstNode *ParseAssignment::parse_assignment(pstr_t str)
{
    AstNode *node = parseNext->parse(str);
    str = node->strtail;
    
    while (1) {
        str = scan(str);
        switch (get_symbol(str)) {
            case SYMBOL_EQUAL:
                node = inject_assignment(node, scan(str+1));
                break;
            case SYMBOL_FOLLOW:
                return node;
        }
        
        str = node->strtail;
    }
}

AstParentNode *ParseAssignment::inject_assignment(AstNode *node, pstr_t str)
{
    if (node->size() == 2) {
        AstParentNode *root = static_cast<AstParentNode*>(node);
        root->children[1] = inject_assignment(root->children[1], str);
        node->strtail = root->children[1]->strtail;

        return root;
    } else {
        AstAssignment *newRoot = new AstAssignment();
        newRoot->strhead = node->strhead;
        std::vector<AstNode*> &newChildren = newRoot->children;

        newChildren.push_back(node);

        str = scan(str);
        AstNode *child = parseNext->parse(str);
        newChildren.push_back(child);

        newRoot->strtail = child->strtail;

        return newRoot;
    }
}

enum ParseAssignment::SymbolType ParseAssignment::get_symbol(pstr_t str)
{
    if (str == line->end()) {
        return SYMBOL_FOLLOW;
    }

    switch (*str) {
        case '=':
            return SYMBOL_EQUAL;
        default:
            return SYMBOL_FOLLOW;
    }
}
