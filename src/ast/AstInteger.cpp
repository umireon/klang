#include "kobject.h"

#include "ast.h"

KInteger* AstInteger::evaluate(Binding* b)
{
    return new KInteger(strtol(get_string().c_str(), NULL, 0));
}
