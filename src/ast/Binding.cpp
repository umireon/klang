#include <map>

#include "kobject.h"
#include "Binding.h"

Binding::~Binding()
{
	std::map<std::string, KObject *>::iterator iter = locals.begin();

	while (iter != locals.end()) {
		delete iter->second;
		iter++;
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
    KObject* func = locals[name];
    return dynamic_cast<KFunction*>(func);
}
