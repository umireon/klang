#include "ast.h"

KObject* Binding::get_local(std::string name)
{
    return locals[name];
}

void Binding::set_local(std::string name, KObject* value)
{
    locals[name] = value;
}

KFunction* Binding::get_function(std::string name)
{
    KObject* func = get_local(name);
    return static_cast<KFunction*>(func);
}
