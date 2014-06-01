#include "kobject/KObject.h"
#include "kobject/KInteger.h"
#include "Binding.h"

#include "ast/AstNode/AstParentNode/AstCompare/AstGreaterThanEqual.h"

KObject *AstGreaterThanEqual::evaluate(Binding *b)
{
    KObject *lhs = children[0]->evaluate(b);
    KObject *rhs = children[1]->evaluate(b);
    KObject *retval = lhs->op_sub(rhs);
    delete lhs;
    delete rhs;
    
    KNumber *knum = static_cast<KNumber *>(retval);
    
    long newValue;
    switch (retval->get_type()) {
        case KObject::INTEGER:
            newValue = knum->to_i() >= 0;
            break;
        case KObject::FLOAT:
            newValue = knum->to_f() > 0;
            break;
        default:
            newValue = 1;
    }
    
    delete retval;
    
    return new KInteger(newValue);
}
