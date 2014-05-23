#include <vector>

#pragma once

enum node_type {
	AST_STATEMENT,
	AST_NUMBER,
	AST_TERM,
	AST_MULTIPLICATION,
	AST_DIVISION,
	AST_STUB,
	AST_UNKNOWN,
	AST_ADDITION,
	AST_SUBTRACTION,
	AST_PAREN,
	AST_PAREN_LEFT,
	AST_PAREN_RIGHT,
	AST_EXPRESSION,
	AST_ELEMENT,
	AST_IDENTIFIER,
	AST_ASSIGNMENT,
};

class AstNode
{
public:
	enum node_type type;
	const char *strhead;
	const char *strtail;
	std::vector<AstNode*> children;
	int value;
	~AstNode();
};
