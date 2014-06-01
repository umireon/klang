#include <map>
#include <sstream>

#include "kobject/KObject.h"
#include "kobject/KFunctionAst.h"
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
    if (locals.count(name) == 1) {
        return locals[name]->clone();
    } else if (global != NULL) {
        return global->get_local(name);
    } else {
        std::ostringstream os;
        os << "Undefined variable: " << name << std::endl;
        throw std::invalid_argument(os.str());
    }
}

void Binding::set_local(std::string name, KObject* value)
{
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
        os << "Undefined function: " << name << std::endl;
        throw std::invalid_argument(os.str());
    }
}
