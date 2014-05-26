#include "kobject.h"

#include "ast.h"

KFloat* AstFloat::evaluate(Binding* b)
{
    return new KFloat(strtod(get_string().c_str(), NULL));
}