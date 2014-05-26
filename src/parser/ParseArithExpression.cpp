#include <sstream>
#include <stdexcept>

#include "ast.h"
#include "Parse.h"

AstNode* ParseArithExpression::parse_arith_expression(const char *str)
{
	AstNode *expr;
	const char *s = str;
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


AstAddition* ParseArithExpression::chain_addition(AstNode* root, const char *str)
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

AstSubtraction* ParseArithExpression::chain_subtraction(AstNode* root, const char *str)
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

const char* ParseArithExpression::scan_lexical_symbol(const char* str)
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
