#include <iostream>
#include <vector>

#include "kobject/KObject.h"
#include "kobject/KNumber.h"
#include "kobject/KNil.h"
#include "kobject/KVector.h"
#include "kfunc/FuncSeq.h"

KObject* FuncSeq::invoke(std::vector<KObject*> args) {
    std::vector<KObject *>::iterator iter = args.begin();
    std::vector<double> list;

    if (args.size() != 2) {
        std::cout << "WARNING: seq arity 2" << std::endl;
    }

    KNumber *first = dynamic_cast<KNumber *>(args[0]);
    KNumber *second = dynamic_cast<KNumber *>(args[1]);

    if (first && second) {
        return invoke(first, second);
    }

    while (iter != args.end()) {
        delete *iter;
        iter++;
    }

    return new KNil();
}

KVector* FuncSeq::invoke(KNumber *first, KNumber *last) {
    long f = first->to_i();
    long l = last->to_i();

    dvector vect(f-l+1);

    for (int i = 0; i <= vect.size(); i++) {
        vect[i] = f + i;
    }

    delete first;
    delete last;

    return new KVector(vect);
}
