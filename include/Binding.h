#pragma once

#include <string>

#include <boost/unordered_map.hpp>

#include "kobject.h"

class KObject;
class KFunction;

class Binding
{
public:
	boost::unordered_map<std::string, long> variableTable;
	boost::unordered_map<std::string, KObject *> locals;
	Binding *global;

	Binding() : global(NULL) {}
	virtual ~Binding();

	KObject* get_local(std::string name);
	void set_local(std::string name, KObject *value);
	KFunction* get_function(std::string name);
};
