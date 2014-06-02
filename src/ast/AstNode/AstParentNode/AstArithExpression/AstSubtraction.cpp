#include "kobject/KObject.h"
#include "Binding.h"

#include "ast/AstSubtraction.h"

KObject* AstSubtraction::evaluate(Binding* b)
{
    KObject *lhs = children[0]->evaluate(b);
    KObject *rhs = children[1]->evaluate(b);

    KObject *retval = lhs->op_sub(rhs);

    delete lhs;
    delete rhs;

    return retval;
}
