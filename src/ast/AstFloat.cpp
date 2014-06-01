#include "kobject.h"

#include "ast/AstFloat.h"

KFloat* AstFloat::evaluate(Binding* b)
{
    return new KFloat(strtod(get_string().c_str(), NULL));
}