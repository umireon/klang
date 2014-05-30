#include "kobject.h"

#include "kfunc/FuncLog.h"

KObject* FuncLog::invoke(std::vector<KObject*> args) {
    KNumber *num = dynamic_cast<KNumber*>(args.at(0));
    
    if (args.size() != 1) {
        throw std::invalid_argument("Arity: 1");
    }
    
    if (!num) {
        throw std::invalid_argument("Argument1 is not a KNumber.");
    }

    return new KFloat(log10(num->to_f()));
}
