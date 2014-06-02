#include <cstdlib>

#include "kobject/KFloat.h"
#include "Binding.h"

#include "ast/AstFloat.h"

KFloat* AstFloat::evaluate(Binding* b)
{
    return new KFloat(value);
}

void AstFloat::save_value()
{
    value = std::strtod(get_string().c_str(), NULL);
}
