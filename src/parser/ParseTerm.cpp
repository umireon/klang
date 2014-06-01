#include <iostream>
#include <sstream>
#include <stdexcept>

#include "ast/AstNode.h"
#include "ast/AstParentNode.h"
#include "ast/AstDivision.h"
#include "ast/AstMultiplication.h"
#include "ast/AstPower.h"
#include "ast/AstReminder.h"

#include "parser/types.h"
#include "parser/ParsePrimary.h"
#include "parser/ParseTerm.h"

AstNode *ParseTerm::parse_term(pstr_t str)
{
	AstNode *term;
	enum SymbolType type = get_symbol(str[0]);
	pstr_t s = str;
    
	switch (type) {
        case SYMBOL_FOLLOW:
            ParsePrimary p;
            term = p.parse_primary(s);
            s = term->strtail;
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
            case SYMBOL_OP_ASTERISK:
                type = get_symbol(s[1]);
                switch (type) {
                    case SYMBOL_OP_ASTERISK:
                        if (term->size() == 2) {
                            AstParentNode *root = static_cast<AstParentNode *>(term);
                            AstNode *child = root->children[1];
                            child = chain_power(child, s+2);
                            term->strtail = child->strtail;
                            root->children[1] = child;
                        } else {
                            term = chain_power(term, s+2);
                        }
                        break;
                    default:
                        term = chain_multiplication(term, s+1);
                        break;
                }
                break;
            case SYMBOL_OP_SLASH:
                term = chain_division(term, s+1);
                break;
            case SYMBOL_OP_PERCENT:
                term = chain_reminder(term, s+1);
                break;
            default:
                return term;
		}
        
		s = term->strtail;
	}
}

AstParentNode *ParseTerm::chain_power(AstNode* node, pstr_t str)
{
	if (node->size() == 2) {
        AstParentNode *root = static_cast<AstParentNode *>(node);
		root->children[1] = chain_power(root->children[1], str);
        return root;
	} else {
		AstPower *newRoot = new AstPower();
		newRoot->strhead = node->strhead;
		std::vector<AstNode *> &newChildren = newRoot->children;
        
		newChildren.push_back(node);
        
		str = scan_lexical_symbol(str);
		ParsePrimary p;
		AstNode *elem = p.parse_primary(str);
		newChildren.push_back(elem);
        
		newRoot->strtail = elem->strtail;
        
		return newRoot;
	}
}

AstMultiplication *ParseTerm::chain_multiplication(AstNode* root, pstr_t str)
{
	AstMultiplication *newRoot = new AstMultiplication();
	newRoot->strhead = root->strhead;
	std::vector<AstNode *> &newChildren = newRoot->children;
    
	newChildren.push_back(root);
    
	str = scan_lexical_symbol(str);
	ParsePrimary p;
	AstNode *elem = p.parse_primary(str);
	newChildren.push_back(elem);
    
	newRoot->strtail = elem->strtail;
    
	return newRoot;
}

AstDivision *ParseTerm::chain_division(AstNode* root, pstr_t str)
{
	AstDivision *newRoot = new AstDivision();
	newRoot->strhead = root->strhead;
	std::vector<AstNode *> &newChildren = newRoot->children;
    
	newChildren.push_back(root);
    
	str = scan_lexical_symbol(str);
	ParsePrimary p;
	AstNode *elem = p.parse_primary(str);
	newChildren.push_back(elem);
    
	newRoot->strtail = elem->strtail;
    
	return newRoot;
}

AstReminder *ParseTerm::chain_reminder(AstNode* root, pstr_t str)
{
	AstReminder *newRoot = new AstReminder();
	newRoot->strhead = root->strhead;
	std::vector<AstNode *> &newChildren = newRoot->children;
    
	newChildren.push_back(root);
    
	str = scan_lexical_symbol(str);
	ParsePrimary p;
	AstNode *elem = p.parse_primary(str);
	newChildren.push_back(elem);
    
	newRoot->strtail = elem->strtail;
    
	return newRoot;
}

pstr_t ParseTerm::scan_lexical_symbol(pstr_t str)
{
	enum SymbolType type;
    
	do {
		type = get_symbol(str[0]);
		str++;
	} while (type == SYMBOL_WHITESPACE);
    
	return str - 1;
}

enum ParseTerm::SymbolType ParseTerm::get_symbol(char c)
{
	switch (c) {
        case ' ':
            return SYMBOL_WHITESPACE;
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
