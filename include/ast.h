#pragma once

#include <string>
#include <vector>
#include <map>

#include "kobject.h"

#include "Binding.h"

#include "ast/AstNode.h"
#include "ast/AstParentNode.h"

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

#include "ast/AstIdentifier.h"

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
