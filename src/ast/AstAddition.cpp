#include "kobject.h"

#include "kobject.h"
#include "ast.h"

KNumber* AstAddition::evaluate(Binding* b)
{
    long valuei = 0;
    double valuef = 0;
    bool isfloat = false;
    std::vector<AstNode*>::iterator iter = children.begin();
    
    while (iter != children.end()) {
        KObject *obj = (*iter)->evaluate(b);
        KNumber *num = static_cast<KNumber*>(obj);
        valuei += num->to_i();
        valuef += num->to_f();
        isfloat = isfloat || (num->get_type() == KNumber::FLOAT);
        iter++;
    }
    
    if (isfloat) {
        return new KFloat(valuef);
    } else {
        return new KInteger(valuei);
    }
}
