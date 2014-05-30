#include "kobject.h"

class FuncMatrix : public KFunction {
    KObject* invoke(std::vector<KObject*> args);
};
