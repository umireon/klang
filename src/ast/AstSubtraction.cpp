#include "kobject.h"

#include "ast.h"

KNumber* AstSubtraction::evaluate(Binding* b)
{
    std::vector<AstNode*>::iterator iter = children.begin();
    KObject *obj = (*iter)->evaluate(b);
    KNumber *num = static_cast<KNumber*>(obj);
    iter++;
    
    long valuei = num->to_i();
    double valuef = num->to_f();
    bool isfloat = num->get_type() == KNumber::FLOAT;
    delete obj;
    
    while (iter != children.end()) {
        obj = (*iter)->evaluate(b);
        num = static_cast<KNumber*>(obj);
        valuei -= num->to_i();
        valuef -= num->to_f();
        isfloat = isfloat || (num->get_type() == KNumber::FLOAT);
        iter++;
        delete obj;
    }
    
    if (isfloat) {
        return new KFloat(valuef);
    } else {
        return new KInteger(valuei);
    }
}
