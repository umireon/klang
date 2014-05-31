#include <iostream>

#include "kobject.h"
#include "kobject/KNil.h"

#include "kfunc/FuncPrint.h"

KObject* FuncPrint::invoke(std::vector<KObject *> args) {
    std::vector<KObject *>::iterator iter = args.begin();

    while (iter != args.end()) {
        KObject *arg = *iter;
        std::cout << arg->to_s();
        iter++;
    }

	return new KNil();
}
