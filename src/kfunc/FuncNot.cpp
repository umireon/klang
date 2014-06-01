#include <vector>

#include "kobject/KObject.h"
#include "kobject/KNumber.h"
#include "kobject/KInteger.h"

#include "kfunc/FuncNot.h"

KObject* FuncNot::invoke(std::vector<KObject*> args) {
    std::vector<KObject *>::iterator iter = args.begin();
    long newValue = 1;

    while (iter != args.end()) {
        KNumber *knum = static_cast<KNumber *>(*iter);

        switch ((*iter)->get_type()) {
            case KObject::NIL:
                newValue = 0;
                break;
            case KObject::INTEGER:
                newValue = newValue && knum->to_i();
                break;
            default:
                ;
        }

        delete *iter;
        iter++;
    }

    return new KInteger(!newValue);
}
