#include "ast.h"

KObject* Binding::get_local(std::string name)
{
	if (locals[name]->get_type() == KObject::FUNCTION) {
		return NULL;
	} else {
	    return locals[name]->clone();
	}
}

void Binding::set_local(std::string name, KObject* value)
{
    locals[name] = value;
}

KFunction* Binding::get_function(std::string name)
{
    KObject* func = locals[name];
    return dynamic_cast<KFunction*>(func);
}
