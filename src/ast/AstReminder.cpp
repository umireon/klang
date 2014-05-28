#include "kobject.h"

#include "ast.h"

KInteger* AstReminder::evaluate(Binding* b)
{
    std::vector<AstNode*>::iterator iter = children.begin();
    KObject *obj = (*iter)->evaluate(b);
    KNumber *num = static_cast<KNumber*>(obj);
    iter++;
    
    long value = num->to_i();
    delete obj;
    
    while (iter != children.end()) {
        obj = (*iter)->evaluate(b);
        num = static_cast<KNumber*>(obj);
        value %= num->to_i();
        iter++;
        delete obj;
    }
    
    return new KInteger(value);
}