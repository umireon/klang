#pragma once

#include <map>
#include <string>
#include <vector>

class AstNode;
class KObject;
class KFunction;

#include "ast/AstNode.h"

#include "kobject/KObject.h"
#include "kobject/KFunction.h"

class Binding
{
public:
	std::map<std::string, KObject *> locals;
	std::vector<AstNode *> functions;
	Binding *global;

	Binding() : global(NULL) {}
	virtual ~Binding();

	KObject* get_local(std::string name);
	void set_local(std::string name, KObject *value);
	KFunction* get_function(std::string name);
};
