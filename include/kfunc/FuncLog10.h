#include "kobject.h"

class FuncLog10 : public KFunction {
    KObject* invoke(std::vector<KObject*> args);
	virtual FuncLog10 *clone() const { return new FuncLog10(*this); }
};
