#include "kobject.h"

class FuncExit : public KFunction {
    KObject* invoke(std::vector<KObject*> args);
};
