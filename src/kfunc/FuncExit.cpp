#include "kobject.h"

#include "kfunc/FuncExit.h"

KObject* FuncExit::invoke(std::vector<KObject*> args) {
    exit(0);
}
