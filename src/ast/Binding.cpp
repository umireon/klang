#include <iostream>
#include <map>
#include <sstream>

#include "kobject/KObject.h"
#include "kobject/KFunctionAst.h"
#include "kobject/KNil.h"
#include "Binding.h"

#include "ast/AstNode.h"

Binding::~Binding()
{
	std::map<std::string, KObject *>::iterator iter = locals.begin();

	while (iter != locals.end()) {
		delete iter->second;
		iter++;
	}
    
	std::vector<AstNode *>::iterator iter2 = functions.begin();
    
	while (iter2 != functions.end()) {
		delete *iter2;
		iter2++;
	}
}

KObject* Binding::get_local(std::string name)
{
    std::map<std::string, KObject *>::iterator item = locals.find(name);

    if (item != locals.end()) {
        return item->second->clone();
    } else if (global != NULL) {
        return global->get_local(name);
    } else {
        std::cout << "WARNING: Undefined Variable " << name << std::endl;
        return new KNil();
    }
}

void Binding::set_local(std::string name, KObject* value)
{
    Binding *parent = this;

    do {
        std::map<std::string, KObject *> &plocals = parent->locals;
        std::map<std::string, KObject *>::iterator item = plocals.find(name);
        if (item != plocals.end()) {
            delete item->second;
            plocals[name] = value->clone();
            return;
        } else {
            parent = parent->global;
        }
    } while (parent != NULL);
    
    locals[name] = value->clone();
}

KFunction* Binding::get_function(std::string name)
{
    if (locals.count(name) == 1) {
        KFunction *f = dynamic_cast<KFunction *>(locals[name]);
        
        if (f == NULL) {
            std::ostringstream os;
            os << "Invoke with Object: " << name << std::endl;
            throw std::invalid_argument(os.str());
        }
        
        return f;
    } else if (global != NULL) {
        return global->get_function(name);
    } else {
        std::ostringstream os;
        std::cout << "Undefined function: " << name << std::endl;
        throw std::invalid_argument(os.str());
    }
}
