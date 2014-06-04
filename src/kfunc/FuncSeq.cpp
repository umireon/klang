#include <iostream>
#include <vector>

#include "kobject/KObject.h"
#include "kobject/KNumber.h"
#include "kobject/KNil.h"
#include "kobject/KVector.h"
#include "kfunc/FuncSeq.h"

KObject* FuncSeq::invoke(std::vector<KObject*> args) {
    if (args.size() == 2) {
        KNumber *first = dynamic_cast<KNumber *>(args[0]);
        KNumber *second = dynamic_cast<KNumber *>(args[1]);

        if (first && second) {
            return invoke(first, second);
        } else {
            std::cout << "WARNING: seq arguments KNumber" << std::endl;
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

KVector* FuncSeq::invoke(KNumber *first, KNumber *last) {
    long f = first->to_i();
    long l = last->to_i();

    dvector vect(l-f+1);

    for (int i = 0; i <= vect.size(); i++) {
        vect[i] = f + i;
    }

    delete first;
    delete last;

    return new KVector(vect);
}
