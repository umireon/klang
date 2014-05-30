#include "kobject.h"

class FuncLog : public KFunction {
    KObject* invoke(std::vector<KObject*> args);
};
