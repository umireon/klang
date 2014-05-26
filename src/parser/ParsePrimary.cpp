#include <iostream>
#include <sstream>
#include <stdexcept>

#include "ast.h"
#include "parser.h"

AstNode* ParsePrimary::parse_primary(const char *str)
{
	enum SymbolType type = get_symbol(str[0]);
    
	switch (type) {
        case SYMBOL_FIRST_NUMBER:
            ParseNumber pn;
            return pn.parse_number(str);
            break;
        case SYMBOL_PAREN_LEFT:
            ParseParen pp;
            return pp.parse_paren(str);
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

AstNode* ParsePrimary::parse_identifier_or_invocation(const char *str)
{
	ParseIdentifier pi;
	AstNode *ident = pi.parse_identifier(str);
    
	str = ident->strtail;
	str = scan_lexical_symbol(str);
	enum SymbolType type = get_symbol(str[0]);
	switch (type) {
        case SYMBOL_PAREN_LEFT:
            str++;
            str = scan_lexical_symbol(str);
            return inject_invocation(ident, str);
            break;
        default:
            return ident;
	}
}

AstParentNode* ParsePrimary::inject_invocation(AstNode* node, const char *str)
{
	if (node->size() == 2) {
        AstParentNode *root = static_cast<AstParentNode*>(node);
		root->children[1] = inject_invocation(root->children[1], str);
        return root;
	} else {
		AstInvocation *newRoot = new AstInvocation();
		newRoot->strhead = node->strhead;
		std::vector<AstNode*> &newChildren = newRoot->children;
		newChildren.push_back(node);
        
        AstArgument *args;
        enum SymbolType type = get_symbol(str[0]);
        switch (type) {
            case SYMBOL_PAREN_RIGHT:
                args = new AstArgument();
                args->strhead = args->strtail = newRoot->strtail = str + 1;
                newRoot->children.push_back(args);
                return newRoot;
            default:
                args = parse_argument(str);
                newRoot->children.push_back(args);
                str = args->strtail;
        }
        
		type = get_symbol(str[0]);
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
}

AstArgument* ParsePrimary::parse_argument(const char *str)
{
	AstArgument *inv = new AstArgument();
	inv->strhead = str;
    
	ParseExpression p;
	AstNode *expr = p.parse_expression(str);
    inv->children.push_back(expr);
    str = expr->strtail;
    
	while (true) {
        str = scan_lexical_symbol(str);
		enum SymbolType type = get_symbol(str[0]);
		switch (type) {
            case SYMBOL_COMMA:
                str++;
                str = scan_lexical_symbol(str);
                expr = p.parse_expression(str);
                inv->children.push_back(expr);
                str = expr->strtail;
                break;
            default:
                inv->strtail = str;
                return inv;
		}
	}
}

const char* ParsePrimary::scan_lexical_symbol(const char* str)
{
	enum SymbolType type;
    
	do {
		type = get_symbol(str[0]);
		str++;
	} while (type == SYMBOL_WHITESPACE);
    
	return str - 1;
}

enum ParsePrimary::SymbolType ParsePrimary::get_symbol(char c)
{
	if ('0' <= c && c <= '9') {
		return SYMBOL_FIRST_NUMBER;
    } else if ('A' <= c && c <= 'Z') {
		return SYMBOL_ALPHABET;
	} else if ('a' <= c && c <= 'z') {
		return SYMBOL_ALPHABET;
    }
    
    switch (c) {
        case ' ':
            return SYMBOL_WHITESPACE;
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
