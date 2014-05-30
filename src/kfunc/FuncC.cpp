#include "kobject.h"

#include "kfunc/FuncC.h"

KObject* FuncC::invoke(std::vector<KObject*> args) {
    dvector vect(args.size());

    for (int i = 0; i < args.size(); i++) {
        KNumber *knum = dynamic_cast<KNumber*>(args[i]);
        if (knum == NULL) {
            throw std::invalid_argument(std::string("not a number"));
        }
        vect[i] = knum->to_f();
    }

	return new KVector(vect);
}
