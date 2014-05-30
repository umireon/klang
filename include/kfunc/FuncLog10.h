#include "kobject.h"

class FuncLog10 : public KFunction {
    KObject* invoke(std::vector<KObject*> args);
};
