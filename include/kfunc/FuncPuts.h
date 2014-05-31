#include "kobject.h"

class FuncPuts : public KFunction {
    KObject* invoke(std::vector<KObject*> args);
	virtual FuncPuts *clone() const { return new FuncPuts(*this); }
};
