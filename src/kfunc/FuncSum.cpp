#include <numeric>
#include <vector>

#include "kobject/KObject.h"
#include "kobject/KNumber.h"
#include "kobject/KInteger.h"

#include "kfunc/FuncSum.h"

KObject* FuncSum::invoke(std::vector<KObject*> args) {
    std::vector<KObject *>::iterator iter = args.begin();
    double newValue = 0;

    while (iter != args.end()) {
        switch ((*iter)->get_type()) {
            case KObject::INTEGER:
            case KObject::FLOAT:
                {
                    KNumber *knum = static_cast<KNumber *>(*iter);
                    newValue += knum->to_f();
                }
                break;
            case KObject::VECTOR:
                {
                    KVector *kvect = static_cast<KVector *>(*iter);
                    dvector &vect = kvect->vect;
                    newValue = std::accumulate(vect.begin(), vect.end(), newValue);
                }
                break;
            default:
                ;
        }

        delete *iter;
        iter++;
    }

    return new KFloat(newValue);
}
