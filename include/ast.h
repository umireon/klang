#pragma once

#include <string>
#include <vector>
#include <map>

#include "kobject.h"

class Binding
{
public:
	std::map<std::string, long> variableTable;
	std::map<std::string, KObject*> locals;
    
	KObject* get_local(std::string name);
	void set_local(std::string name, KObject* value);
    
	KFunction* get_function(std::string name);
};

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

class AstNode
{
public:
	enum node_type type;
	const char *strhead;
	const char *strtail;
    
    virtual ~AstNode() {}
    virtual int size() { return 0; }
	virtual std::string get_string();
	virtual KObject* evaluate(Binding* b) { return NULL; }
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
	KNumber* evaluate(Binding* b);
};

class AstSubtraction : public AstParentNode {
public:
    AstSubtraction() { type = AST_SUBTRACTION; }
	KNumber* evaluate(Binding* b);
};

class AstMultiplication : public AstParentNode {
public:
    AstMultiplication() { type = AST_MULTIPLICATION; }
	KNumber* evaluate(Binding* b);
};

class AstDivision : public AstParentNode {
public:
    AstDivision() { type = AST_DIVISION; }
	KNumber* evaluate(Binding* b);
};

class AstReminder : public AstParentNode {
public:
    AstReminder() { type = AST_REMINDER; }
	KInteger* evaluate(Binding* b);
};

class AstPower : public AstParentNode {
public:
    AstPower() { type = AST_POWER; }
	KNumber* evaluate(Binding* b);
};

class AstParen : public AstParentNode {
public:
    AstParen() { type = AST_PAREN; }
	KObject* evaluate(Binding* b);
};

class AstNumber : public AstNode {
public:
    AstNumber() { type = AST_NUMBER; }
	virtual KNumber* evaluate(Binding* b) = 0;
};

class AstInteger : public AstNumber {
public:
    AstInteger() { type = AST_INTEGER; }
	KInteger* evaluate(Binding* b);
};

class AstHexdecimal : public AstInteger {
};

class AstOctal : public AstInteger {
};

class AstDecimal : public AstInteger {
};

class AstFloat : public AstNumber {
public:
    AstFloat() { type = AST_FLOAT; }
	KFloat* evaluate(Binding* b);
};

class AstIdentifier : public AstNode {
public:
    AstIdentifier() { type = AST_IDENTIFIER; }
	KObject* evaluate(Binding* b);
};

class AstAssignment : public AstParentNode {
public:
    AstAssignment() { type = AST_ASSIGNMENT; }
	KObject* evaluate(Binding* b);
};

class AstInvocation : public AstParentNode {
public:
    AstInvocation() { type = AST_INVOCATION; }
    KObject* evaluate(Binding* b);
};

class AstArgument : public AstParentNode {
public:
    AstArgument() { type = AST_ARGUMENT; }
};
