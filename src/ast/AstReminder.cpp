#include "kobject.h"

#include "ast/AstReminder.h"

KObject* AstReminder::evaluate(Binding* b)
{
    KObject *lhs = children[0]->evaluate(b);
    KObject *rhs = children[1]->evaluate(b);

    KObject *retval = lhs->op_rem(rhs);

    delete lhs;
    delete rhs;

    return retval;
}