#include <algorithm>

#include "kobject/KObject.h"
#include "kobject/KNumber.h"
#include "kobject/KFloat.h"
#include "kobject/KNil.h"
#include "kobject/KFunction.h"

#include "kfunc/triangle.h"

KObject* FuncMath::invoke(std::vector<KObject*> args) {
    if (args.size() == 1) {
        switch (args[0]->get_type()) {
            case KObject::INTEGER:
            case KObject::FLOAT:
                {
                    KNumber *knum = static_cast<KNumber *>(args[0]);
                    double value = knum->to_f();
                    delete knum;
                    return new KFloat(sin(value));
                }
            case KObject::VECTOR:
                {
                    KVector *kvect = static_cast<KVector *>(args[0]);
                    dvector &vect = kvect->vect;
                    std::transform(vect.begin(), vect.end(), vect.begin(), mathfunc);
                    return kvect;
                }
            default:
                ;
        }
    } else {
        std::cout << "WARNING: seq arity 2" << std::endl;
    }

    std::vector<KObject *>::iterator iter = args.begin();
    while (iter != args.end()) {
        delete *iter;
        iter++;
    }

    return new KNil();
}
