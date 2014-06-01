#pragma once

#include "ast/AstNode.h"
#include "ast/AstNode/AstParentNode/AstCompare.h"
#include "ast/AstNode/AstParentNode/AstCompare/AstGreaterThanEqual.h"
#include "ast/AstNode/AstParentNode/AstCompare/AstGreaterThan.h"
#include "ast/AstNode/AstParentNode/AstCompare/AstLessThanEqual.h"
#include "ast/AstNode/AstParentNode/AstCompare/AstLessThan.h"

#include "parser/types.h"

class ParseCompare {
public:
    AstNode *parse_compare(pstr_t str);
protected:
    enum SymbolType {
        SYMBOL_LESS,
        SYMBOL_GREATER,
        SYMBOL_EQUAL,
        SYMBOL_WHITESPACE,
        SYMBOL_FOLLOW,
    };

    AstLessThanEqual *chain_less_than_equal(AstNode* root, pstr_t str);
    AstLessThan *chain_less_than(AstNode* root, pstr_t str);
    AstGreaterThanEqual *chain_greater_than_equal(AstNode* root, pstr_t str);
    AstGreaterThan *chain_greater_than(AstNode* root, pstr_t str);
    
    enum SymbolType get_symbol(char c);
    pstr_t scan(pstr_t str);
};
