#include "kobject.h"

#include "ast/AstPower.h"

KObject* AstPower::evaluate(Binding* b)
{
    KObject *lhs = children[0]->evaluate(b);
    KObject *rhs = children[1]->evaluate(b);

    KObject *retval = lhs->op_pow(rhs);

    delete lhs;
    delete rhs;

    return retval;
}
