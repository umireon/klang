#include <vector>

#include "kobject/KObject.h"
#include "kobject/KNumber.h"
#include "kobject/KInteger.h"

#include "kfunc/FuncOr.h"

KObject* FuncOr::invoke(std::vector<KObject*> args) {
    std::vector<KObject *>::iterator iter = args.begin();
    long newValue = 0;
    
    while (iter != args.end()) {
        KNumber *knum = static_cast<KNumber *>(*iter);
        
        switch ((*iter)->get_type()) {
            case KObject::NIL:
                break;
            case KObject::INTEGER:
                newValue = newValue || knum->to_i();
                break;
            default:
                newValue = 1;
        }
        
        delete *iter;
        iter++;
    }
    
    return new KInteger(newValue);
}
