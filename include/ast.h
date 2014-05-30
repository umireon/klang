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

class AstNode
{
public:
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
	virtual KObject* evaluate(Binding* b);
};

class AstSubtraction : public AstParentNode {
public:
	virtual KObject* evaluate(Binding* b);
};

class AstMultiplication : public AstParentNode {
public:
	virtual KObject* evaluate(Binding* b);
};

class AstDivision : public AstParentNode {
public:
	virtual KObject* evaluate(Binding* b);
};

class AstReminder : public AstParentNode {
public:
	virtual KObject* evaluate(Binding* b);
};

class AstPower : public AstParentNode {
public:
	virtual KObject* evaluate(Binding* b);
};

class AstParen : public AstParentNode {
public:
	virtual KObject* evaluate(Binding* b);
};

class AstNumber : public AstNode {
public:
	virtual KNumber* evaluate(Binding* b) = 0;
};

class AstInteger : public AstNumber {
public:
	virtual KInteger* evaluate(Binding* b);
};

class AstHexdecimal : public AstInteger {
};

class AstOctal : public AstInteger {
};

class AstDecimal : public AstInteger {
};

class AstFloat : public AstNumber {
public:
	virtual KFloat* evaluate(Binding* b);
};

class AstIdentifier : public AstNode {
public:
	enum IdentifierType {
		NAME,
		FUNCTION
	};

	virtual KObject* evaluate(Binding* b);
	IdentifierType get_identifier_type();
};

class AstAssignment : public AstParentNode {
public:
	virtual KObject* evaluate(Binding* b);
};

class AstArgument : public AstParentNode {
public:
};

class AstInvocation : public AstNode {
public:
	AstIdentifier *ident;
	AstArgument *astArgs;

    virtual ~AstInvocation();

    virtual KObject* evaluate(Binding* b);
};
