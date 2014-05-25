#include <string>
#include <vector>

#pragma once

enum node_type {
	AST_STATEMENT,
	AST_EXPRESSION,
	AST_ADDITION,
	AST_SUBTRACTION,
	AST_TERM,
	AST_MULTIPLICATION,
	AST_DIVISION,
	AST_ELEMENT,
	AST_NUMBER,
	AST_PAREN,
	AST_PAREN_LEFT,
	AST_PAREN_RIGHT,
	AST_IDENTIFIER,
	AST_ASSIGNMENT,
	AST_STUB,
	AST_UNKNOWN,
	AST_POWER,
	AST_REMINDER,
};

class AstNode
{
public:
	enum node_type type;
	const char *strhead;
	const char *strtail;

    virtual ~AstNode() {}
    virtual int size() { return 0; }
	virtual long get_long() { return 0; }
	virtual double get_double() { return 0; }
	virtual std::string get_string();
};

class AstParentNode : public AstNode {
public:
	std::vector<AstNode*> children;
    
    virtual ~AstParentNode();
	virtual int size() { return children.size(); }
};

class AstAddition : public AstParentNode {
public:
    AstAddition() { type = AST_ADDITION; }
};

class AstSubtraction : public AstParentNode {
public:
    AstSubtraction() { type = AST_SUBTRACTION; }
};

class AstMultiplication : public AstParentNode {
public:
    AstMultiplication() { type = AST_MULTIPLICATION; }
};

class AstDivision : public AstParentNode {
public:
    AstDivision() { type = AST_DIVISION; }
};

class AstReminder : public AstParentNode {
public:
    AstReminder() { type = AST_REMINDER; }
};

class AstPower : public AstParentNode {
public:
    AstPower() { type = AST_POWER; }
};

class AstParen : public AstParentNode {
public:
    AstParen() { type = AST_PAREN; }
	long get_long();
};

class AstNumber : public AstNode {
public:
    AstNumber() { type = AST_NUMBER; }
};

class AstInteger : public AstNumber {
public:
	long get_long();
	double get_double();
};

class AstHexdecimal : public AstInteger {
};

class AstOctal : public AstInteger {
};

class AstDecimal : public AstInteger {
};

class AstFloat : public AstInteger {
public:
	long get_long();
	double get_double();
};

class AstIdentifier : public AstNode {
public:
    AstIdentifier() { type = AST_IDENTIFIER; }
};
