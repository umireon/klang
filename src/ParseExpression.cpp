#include <sstream>

#include "ast.h"
#include "parser.h"

AstNode* ParseExpression::parse_expression(const char *str)
{
	AstNode *expr;
	const char *s = str;
	enum symbol_type type;

	type = get_symbol(str[0]);
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


AstNode* ParseExpression::chain_addition(AstNode* root, const char *str)
{
	AstNode *newRoot = new AstAddition();
	newRoot->strhead = root->strhead;
	std::vector<AstNode*> &newChildren = newRoot->children;

	newChildren.push_back(root);
	ParseTerm p;
	AstNode *term = p.parse_term(str);
	newChildren.push_back(term);

	newRoot->strtail = term->strtail;

	return newRoot;
}

AstNode* ParseExpression::chain_subtraction(AstNode* root, const char *str)
{
	AstNode *newRoot = new AstSubtraction();
	newRoot->strhead = root->strhead;
	std::vector<AstNode*> &newChildren = newRoot->children;

	newChildren.push_back(root);
	ParseTerm p;
	AstNode *term = p.parse_term(str);
	newChildren.push_back(term);

	newRoot->strtail = term->strtail;

	return newRoot;
}

enum symbol_type ParseExpression::get_symbol(char c)
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
		return SYMBOL_UNKNOWN;
	}
}
