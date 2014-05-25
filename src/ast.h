#include <string>
#include <vector>
#include <map>

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
	AST_FLOAT,
	AST_INTEGER,
	AST_INVOCATION,
	AST_ARGUMENT,
};

class Binding
{
public:
	std::map<std::string, double> variableTable;
};

class AstNode
{
public:
	enum node_type type;
	const char *strhead;
	const char *strtail;

    virtual ~AstNode() {}
    virtual int size() { return 0; }
	virtual long get_long(Binding* b) { return 0; }
	virtual double get_double(Binding* b) { return 0; }
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
    long get_long(Binding* b);
    double get_double(Binding* b);
};

class AstSubtraction : public AstParentNode {
public:
    AstSubtraction() { type = AST_SUBTRACTION; }
    long get_long(Binding* b);
    double get_double(Binding* b);
};

class AstMultiplication : public AstParentNode {
public:
    AstMultiplication() { type = AST_MULTIPLICATION; }
    long get_long(Binding* b);
    double get_double(Binding* b);
};

class AstDivision : public AstParentNode {
public:
    AstDivision() { type = AST_DIVISION; }
    long get_long(Binding* b);
    double get_double(Binding* b);
};

class AstReminder : public AstParentNode {
public:
    AstReminder() { type = AST_REMINDER; }
    long get_long(Binding* b);
    double get_double(Binding* b);
};

class AstPower : public AstParentNode {
public:
    AstPower() { type = AST_POWER; }
    long get_long(Binding* b);
    double get_double(Binding* b);
};

class AstParen : public AstParentNode {
public:
    AstParen() { type = AST_PAREN; }
	long get_long(Binding* b);
    double get_double(Binding* b);
};

class AstNumber : public AstNode {
public:
    AstNumber() { type = AST_NUMBER; }
};

class AstInteger : public AstNumber {
public:
    AstInteger() { type = AST_INTEGER; }
	long get_long(Binding* b);
	double get_double(Binding* b);
};

class AstHexdecimal : public AstInteger {
};

class AstOctal : public AstInteger {
};

class AstDecimal : public AstInteger {
};

class AstFloat : public AstInteger {
public:
    AstFloat() { type = AST_FLOAT; }
	long get_long(Binding* b);
	double get_double(Binding* b);
};

class AstIdentifier : public AstNode {
public:
    AstIdentifier() { type = AST_IDENTIFIER; }
	long get_long(Binding* b);
	double get_double(Binding* b);
};

class AstAssignment : public AstParentNode {
public:
    AstAssignment() { type = AST_ASSIGNMENT; }
	long get_long(Binding* b);
	double get_double(Binding* b);
};

class AstInvocation : public AstParentNode {
public:
    AstInvocation() { type = AST_INVOCATION; }
	long get_long(Binding* b);
	double get_double(Binding* b);
};

class AstArgument : public AstParentNode {
public:
    AstArgument() { type = AST_ARGUMENT; }
};