#include <iostream>

#include "kobject.h"
#include "kobject/KNil.h"

#include "kfunc/FuncPuts.h"

KObject* FuncPuts::invoke(std::vector<KObject *> args) {
    std::vector<KObject *>::iterator iter = args.begin();

    while (iter != args.end()) {
        output << (*iter)->to_s() << std::endl;
        delete *iter;
        iter++;
    }

	return new KNil();
}
