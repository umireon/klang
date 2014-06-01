#include <cstdlib>

#include "kobject/KInteger.h"
#include "Binding.h"

#include "ast/AstInteger.h"

KInteger* AstInteger::evaluate(Binding* b)
{
    return new KInteger(value);
}

void AstInteger::save_value()
{
    value = std::strtol(get_string().c_str(), NULL, 0);
}