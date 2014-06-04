#include "kobject.h"

#include <vector>

#include "kfunc/FuncC.h"

KObject* FuncC::invoke(std::vector<KObject*> args) {
    std::vector<KObject *>::iterator iter = args.begin();
    std::vector<double> list;

    while (iter != args.end()) {
        switch ((*iter)->get_type()) {
            case KObject::INTEGER:
            case KObject::FLOAT:
                {
                    KNumber *knum = static_cast<KNumber *>(*iter);
                    list.push_back(knum->to_f());
                }
                break;
            case KObject::VECTOR:
                {
                    KVector *kvect = static_cast<KVector *>(*iter);
                    dvector &vect = kvect->vect;
                    list.insert(list.end(), vect.begin(), vect.end());
                }
                break;
            default:
                ;
        }

        delete *iter;
        iter++;
    }

    dvector vect(list.size());
    for (int i = 0; i < list.size(); i++) {
        vect[i] = list[i];
    }
	return new KVector(vect);
}
