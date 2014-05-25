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

class Object {
public:
	virtual std::string to_string() { return std::string("Object"); }
};

class Number : public Object {
public:
	enum Type {
		INTEGER,
		FLOAT
	};

	enum Type type;

	virtual ~Number() {}
	virtual std::string to_string() { return std::string("Number"); }
	virtual long to_i() = 0;
	virtual double to_f() = 0;
};

class Integer : public Number {
public:
	long value;

	Integer(long v) { type = INTEGER; value = v; }
	long to_i() { return value; }
	double to_f() { return value; }
	std::string to_string() { return std::string("Integer"); }
};

class Float : public Number {
public:
	double value;

	Float(double v) { type = FLOAT; value = v; }
	long to_i() { return value; }
	double to_f() { return value; }
	std::string to_string() { return std::string("Float"); }
};

class Function : public Object {
public:
	virtual Object* invoke(std::vector<Object*> args) = 0;
	std::string to_string() { return std::string("Function"); }
};

class Binding
{
public:
	std::map<std::string, long> variableTable;
	std::map<std::string, Object*> locals;

	Object* get_local(std::string name);
	void set_local(std::string name, Object* value);

	Function* get_function(std::string name);
};

class AstNode : public Object
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
	virtual Object* evaluate(Binding* b) { return NULL; }
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
	Number* evaluate(Binding* b);
};

class AstSubtraction : public AstParentNode {
public:
    AstSubtraction() { type = AST_SUBTRACTION; }
	Number* evaluate(Binding* b);
};

class AstMultiplication : public AstParentNode {
public:
    AstMultiplication() { type = AST_MULTIPLICATION; }
	Number* evaluate(Binding* b);
};

class AstDivision : public AstParentNode {
public:
    AstDivision() { type = AST_DIVISION; }
	Number* evaluate(Binding* b);
};

class AstReminder : public AstParentNode {
public:
    AstReminder() { type = AST_REMINDER; }
	Integer* evaluate(Binding* b);
};

class AstPower : public AstParentNode {
public:
    AstPower() { type = AST_POWER; }
	Number* evaluate(Binding* b);
};

class AstParen : public AstParentNode {
public:
    AstParen() { type = AST_PAREN; }
	Object* evaluate(Binding* b);
};

class AstNumber : public AstNode {
public:
    AstNumber() { type = AST_NUMBER; }
	virtual Number* evaluate(Binding* b) = 0;
};

class AstInteger : public AstNumber {
public:
    AstInteger() { type = AST_INTEGER; }
	Integer* evaluate(Binding* b);
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
	Float* evaluate(Binding* b);
};

class AstIdentifier : public AstNode {
public:
    AstIdentifier() { type = AST_IDENTIFIER; }
	Object* evaluate(Binding* b);
};

class AstAssignment : public AstParentNode {
public:
    AstAssignment() { type = AST_ASSIGNMENT; }
	Object* evaluate(Binding* b);
};

class AstInvocation : public AstParentNode {
public:
    AstInvocation() { type = AST_INVOCATION; }
    Object* evaluate(Binding* b);
};

class AstArgument : public AstParentNode {
public:
    AstArgument() { type = AST_ARGUMENT; }
};
