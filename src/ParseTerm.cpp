#include <iostream>
#include <sstream>
#include <stdexcept>

#include "ast.h"
#include "parser.h"

AstNode* ParseTerm::parse_term(const char *str)
{
	AstNode *term;
	const char *s = str;
	enum symbol_type type;

	type = get_symbol(s[0]);
	switch (type) {
	case SYMBOL_NUMBER_ZERO:
	case SYMBOL_NUMBER_OCT:
	case SYMBOL_NUMBER_DEC:
	case SYMBOL_SIGN_MINUS:
	case SYMBOL_SIGN_PLUS:
	case SYMBOL_PAREN_LEFT:
	case SYMBOL_ALPHABET_HEXUPPER:
	case SYMBOL_ALPHABET_HEXLOWER:
	case SYMBOL_ALPHABET_X:
	case SYMBOL_ALPHABET:
		term = p.parse_element(s);
		s = term->strtail;
		break;
	default:
        std::ostringstream os;
        os << "Unexpected character: " << s[0] << std::endl;
        throw std::invalid_argument(os.str());
	}

	while (1) {
		type = get_symbol(s[0]);
		switch (type) {
		case SYMBOL_OP_ASTERISK:
			type = get_symbol(s[1]);
			switch (type) {
			case SYMBOL_OP_ASTERISK:
				if (term->size() == 2) {
					AstNode *child = term->children[1];
					child = chain_power(child, s+2);
					term->strtail = child->strtail;
					term->children[1] = child;
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
		default:
			return term;
		}

		s = term->strtail;
	}
}

AstNode* ParseTerm::chain_power(AstNode* root, const char *str)
{
	if (root->size() == 2) {
		root->children[1] = chain_power(root->children[1], str);
	} else {
		AstNode *newRoot = new AstPower();
		newRoot->strhead = root->strhead;
		std::vector<AstNode*> &newChildren = newRoot->children;

		newChildren.push_back(root);
		AstNode *elem = p.parse_element(str);
		newChildren.push_back(elem);

		newRoot->strtail = elem->strtail;

		return newRoot;
	}
}

AstNode* ParseTerm::chain_multiplication(AstNode* root, const char *str)
{
	AstNode *newRoot = new AstMultiplication();
	newRoot->strhead = root->strhead;
	std::vector<AstNode*> &newChildren = newRoot->children;

	newChildren.push_back(root);
	AstNode *elem = p.parse_element(str);
	newChildren.push_back(elem);

	newRoot->strtail = elem->strtail;

	return newRoot;
}

AstNode* ParseTerm::chain_division(AstNode* root, const char* str)
{
	AstNode *newRoot = new AstDivision();
	newRoot->strhead = root->strhead;
	std::vector<AstNode*> &newChildren = newRoot->children;

	newChildren.push_back(root);
	AstNode *elem = p.parse_element(str);
	newChildren.push_back(elem);

	newRoot->strtail = elem->strtail;

	return newRoot;
}

enum symbol_type ParseTerm::get_symbol(char c)
{
	char dc = c | 0x20;

	if (c == '0') {
		return SYMBOL_NUMBER_ZERO;
	} else if ('1' <= c && c <= '7') {
		return SYMBOL_NUMBER_OCT;
	} else if (c == '8' || c == '9') {
		return SYMBOL_NUMBER_DEC;
	} else if ('A' <= c && c <= 'F') {
		return SYMBOL_ALPHABET_HEXUPPER;
	} else if ('a' <= c && c <= 'f') {
		return SYMBOL_ALPHABET_HEXLOWER;
	} else if (dc == 'x') {
		return SYMBOL_ALPHABET_X;
	} else if ('g' <= dc && dc <= 'z') {
		return SYMBOL_ALPHABET;
	} else if (c == '*') {
		return SYMBOL_OP_ASTERISK;
	} else if (c == '/') {
		return SYMBOL_OP_SLASH;
	} else if (c == '%') {
		return SYMBOL_OP_PERCENT;
	} else if (c == '+') {
		return SYMBOL_SIGN_PLUS;
	} else if (c == '+') {
		return SYMBOL_SIGN_PLUS;
	} else if (c == '-') {
		return SYMBOL_SIGN_MINUS;
	} else if (c == '(') {
		return SYMBOL_PAREN_LEFT;
	} else if (c == ')') {
		return SYMBOL_PAREN_RIGHT;
	} else if (c == '.') {
		return SYMBOL_DOT;
	} else if (c == '\0') {
		return SYMBOL_NULL;
	} else {
		return SYMBOL_FOLLOW;
	}
}