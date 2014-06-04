#pragma once

#include "ast/AstNode.h"
#include "ast/AstNode/AstParentNode/AstCompare.h"
#include "ast/AstNode/AstParentNode/AstCompare/AstGreaterThanEqual.h"
#include "ast/AstNode/AstParentNode/AstCompare/AstGreaterThan.h"
#include "ast/AstNode/AstParentNode/AstCompare/AstLessThanEqual.h"
#include "ast/AstNode/AstParentNode/AstCompare/AstLessThan.h"

#include "parser/types.h"
#include "parser/BaseParse.h"

class ParseCompare : public BaseParse {
public:
    BaseParse *parseNext;

    virtual AstNode *parse(pstr_t str)
    {
        return parse_compare(str);
    }

    AstNode *parse_compare(pstr_t str);
protected:
    enum SymbolType {
        SYMBOL_LESS,
        SYMBOL_GREATER,
        SYMBOL_EQUAL,
        SYMBOL_FOLLOW,
    };

    AstLessThanEqual *chain_less_than_equal(AstNode* root, pstr_t str);
    AstLessThan *chain_less_than(AstNode* root, pstr_t str);
    AstGreaterThanEqual *chain_greater_than_equal(AstNode* root, pstr_t str);
    AstGreaterThan *chain_greater_than(AstNode* root, pstr_t str);
    
    enum SymbolType get_symbol(pstr_t str);
};
