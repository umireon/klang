#include <iostream>

#include "kobject.h"
#include "kobject/KNil.h"

#include "kfunc/FuncPrint.h"

KObject* FuncPrint::invoke(std::vector<KObject *> args) {
    std::vector<KObject *>::iterator iter = args.begin();

    while (iter != args.end()) {
        output << (*iter)->to_s();
        delete *iter;
        iter++;
    }

	return new KNil();
}
