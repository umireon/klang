#include "kobject.h"
#include "kobject/KMatrix.h"

#include "kfunc/FuncMatrix.h"

KObject* FuncMatrix::invoke(std::vector<KObject*> args) {
    KVector *kvect = dynamic_cast<KVector*>(args[0]);
    long nrow = static_cast<KNumber*>(args[1])->to_i();
    long ncol = static_cast<KNumber*>(args[2])->to_i();

    dvector::iterator iter = kvect->vect.begin();

    dmatrix m = dmatrix(nrow, ncol);

    for (long i = 0; i < nrow; i++) {
        for (long j = 0; j < ncol; j++) {
            m(i,j) = *iter;
            iter++;
        }
    }

    return new KMatrix(m);
}
