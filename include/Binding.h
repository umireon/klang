#pragma once

#include <string>
#include <map>

#include "kobject.h"

class KObject;
class KFunction;

class Binding
{
public:
	std::map<std::string, long> variableTable;
	std::map<std::string, KObject *> locals;
    
	KObject* get_local(std::string name);
	void set_local(std::string name, KObject *value);
    
	KFunction* get_function(std::string name);
};
