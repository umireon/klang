#include "kobject.h"

#include "ast.h"

KNumber* AstDivision::evaluate(Binding* b)
{
    std::vector<AstNode*>::iterator iter = children.begin();
    KObject *obj = (*iter)->evaluate(b);
    KNumber *num = static_cast<KNumber*>(obj);
    iter++;
    
    long valuei = num->to_i();
    double valuef = num->to_f();
    bool isfloat = num->type == KNumber::FLOAT;
    
    while (iter != children.end()) {
        obj = (*iter)->evaluate(b);
        num = static_cast<KNumber*>(obj);
        if (!isfloat) {
            valuei /= num->to_i();
        }
        valuef /= num->to_f();
        isfloat = isfloat || (num->type == KNumber::FLOAT);
        iter++;
    }
    
    if (isfloat) {
        return new KFloat(valuef);
    } else {
        return new KInteger(valuei);
    }
}