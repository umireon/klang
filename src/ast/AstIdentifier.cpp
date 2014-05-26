#include "kobject.h"

#include "ast.h"

KObject* AstIdentifier::evaluate(Binding* b)
{
    std::string name = get_string();
    return b->get_local(name);
}