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
	std::vector<AstNode*> children;
	int value;
	virtual ~AstNode();
	virtual std::string get_type_name()
	{
		return "AstNode";
	}
	virtual int size()
	{
		return children.size();
	}
};

class AstStatement : public AstNode
{
public:
	AstStatement()
	{
		this->type = AST_STATEMENT;
	}
};

class AstExpression : public AstNode
{
public:
	AstExpression()
	{
		this->type = AST_EXPRESSION;
	}
};

class AstAddition : public AstNode
{
public:
	AstAddition()
	{
		this->type = AST_ADDITION;
	}
};

class AstSubtraction : public AstNode
{
public:
	AstSubtraction()
	{
		this->type = AST_SUBTRACTION;
	}
};

class AstTerm : public AstNode
{
public:
	AstTerm()
	{
		this->type = AST_TERM;
	}
};

class AstMultiplication : public AstNode
{
public:
	AstMultiplication()
	{
		this->type = AST_MULTIPLICATION;
	}
};

class AstDivision : public AstNode
{
public:
	AstDivision()
	{
		this->type = AST_DIVISION;
	}
};

class AstReminder : public AstNode
{
public:
	AstReminder()
	{
		this->type = AST_REMINDER;
	}
};

class AstElement : public AstNode
{
public:
	AstElement()
	{
		this->type = AST_ELEMENT;
	}
};

class AstPower : public AstNode
{
public:
	AstPower()
	{
		this->type = AST_POWER;
	}
};

class AstParen : public AstNode
{
public:
	AstParen()
	{
		this->type = AST_PAREN;
	}
};

class AstNumber : public AstNode
{
public:
	AstNumber()
	{
		this->type = AST_NUMBER;
	}
	int size()
	{
		return 0;
	}
	virtual long get_long() = 0;
	virtual double get_double() = 0;
};

class AstInteger : public AstNumber
{
public:
	long get_long();
	double get_double();
};

class AstHexdecimal : public AstInteger
{
};

class AstOctal : public AstInteger
{
};

class AstDecimal : public AstInteger
{
};

class AstFloat : public AstInteger
{
	long get_long();
	double get_double();
};

class AstIdentifier : public AstNode
{
public:
	AstIdentifier()
	{
		this->type = AST_IDENTIFIER;
	}
};
