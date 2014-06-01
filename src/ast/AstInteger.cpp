#include "kobject/KInteger.h"
#include "Binding.h"

#include "ast/AstInteger.h"

KInteger* AstInteger::evaluate(Binding* b)
{
    return new KInteger(strtol(get_string().c_str(), NULL, 0));
}
