#include "kobject/KObject.h"

#include "ast/AstAssignment.h"
#include "Binding.h"

KObject* AstAssignment::evaluate(Binding* b)
{
    std::string name = children.at(0)->get_string();
    KObject *value = children.at(1)->evaluate(b);
    b->set_local(name, value);
    return value;
}
