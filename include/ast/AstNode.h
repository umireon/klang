#pragma once

#include "Binding.h"
#include "kobject.h"

class AstNode
{
public:
	const char *strhead;
	const char *strtail;
    
    virtual ~AstNode() {}
    virtual int size() { return 0; }
	virtual std::string get_string();
	virtual KObject* evaluate(Binding* b) { throw std::invalid_argument(std::string("evaluation not defined.")); }
};
