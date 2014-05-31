#include <iostream>

#include "kobject.h"
#include "kobject/KNil.h"

#include "kfunc/FuncPuts.h"

KObject* FuncPuts::invoke(std::vector<KObject *> args) {
    std::vector<KObject *>::iterator iter = args.begin();

    while (iter != args.end()) {
        KObject *arg = *iter;
        std::cout << arg->to_s() << std::endl;
        iter++;
    }

	return new KNil();
}
