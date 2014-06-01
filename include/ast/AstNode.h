#pragma once

#include "kobject/KObject.h"
#include "Binding.h"

#include "parser/types.h"

class AstNode
{
public:
	pstr_t strhead;
	pstr_t strtail;
    
    virtual ~AstNode() {}
    virtual int size() { return 0; }
	virtual std::string get_string();
	virtual KObject *evaluate(Binding *b) { throw std::invalid_argument(std::string("evaluation not defined.")); }
};
