#include <stdexcept>

#include "kobject.h"

#include "ast.h"

KObject* AstMultiplication::evaluate(Binding* b)
{
    KObject *lhs = children[0]->evaluate(b);
    KObject *rhs = children[1]->evaluate(b);

    KObject *retval = lhs->op_mul(rhs);

    return retval;
}
