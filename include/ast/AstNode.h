#pragma once

#include <iostream>
#include <string>

class Binding;

#include "kobject/KObject.h"
#include "kobject/KNil.h"
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
	virtual KObject *evaluate(Binding *b) {
        std::cout << "WARNING: evaluation not defined." << std::endl;
        return new KNil();
    }
};
