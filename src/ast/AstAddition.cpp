#include "kobject.h"

#include "ast/AstAddition.h"

KObject* AstAddition::evaluate(Binding* b)
{
    KObject *lhs = children[0]->evaluate(b);
    KObject *rhs = children[1]->evaluate(b);

    KObject *retval = lhs->op_add(rhs);

    delete lhs;
    delete rhs;

    return retval;
}
