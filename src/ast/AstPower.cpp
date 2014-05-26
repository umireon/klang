#include "kobject.h"

#include "ast.h"

KNumber* AstPower::evaluate(Binding* b)
{
    KNumber *baseNum = static_cast<KNumber*>(children.at(0)->evaluate(b));
    KNumber *eNum = static_cast<KNumber*>(children.at(1)->evaluate(b));
    
    if (baseNum->type == KNumber::FLOAT || eNum->type == KNumber::FLOAT) {
        return new KFloat(pow(baseNum->to_f(), eNum->to_i()));
    } else {
        long base = baseNum->to_i();
        long num = eNum->to_i();
        long value = 1;
        for (int i = 0; i < num; i++) {
            value *= base;
        }
        return new KInteger(value);
    }
}