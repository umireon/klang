#include "ast.h"

KObject* Binding::get_local(std::string name)
{
    if (locals.count(name) == 1) {
        return locals[name]->clone();
    } else {
        return NULL;
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
