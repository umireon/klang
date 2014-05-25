#include <sstream>
#include <stdexcept>

#include "ast.h"
#include "Parse.h"

AstNode* ParseAssignment::parse_assignment(const char *str)
{
	ParseArithExpression p;

	AstNode *expr = p.parse_arith_expression(str);
	str = expr->strtail;
	str = scan_lexical_symbol(str);
	if (str[0] == '=') {
		str++;
		return chain_assignment(expr, str);
	} else {
		return expr;
	}
}

AstParentNode* ParseAssignment::chain_assignment(AstNode* node, const char *str)
{
	if (node->size() == 2) {
        AstParentNode *root = static_cast<AstParentNode*>(node);
		root->children[1] = chain_assignment(root->children[1], str);
        return root;
	} else {
		AstAssignment *newRoot = new AstAssignment();
		newRoot->strhead = node->strhead;
		std::vector<AstNode*> &newChildren = newRoot->children;

		newChildren.push_back(node);

		str = scan_lexical_symbol(str);
		ParseExpression p;
		AstNode *elem = p.parse_expression(str);
		newChildren.push_back(elem);

		newRoot->strtail = elem->strtail;

		return newRoot;
	}
}

const char* ParseAssignment::scan_lexical_symbol(const char* str)
{
	enum SymbolType type;

	do {
		type = get_symbol(str[0]);
		str++;
	} while (type == SYMBOL_WHITESPACE);

	return str - 1;
}

enum ParseAssignment::SymbolType ParseAssignment::get_symbol(char c)
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
