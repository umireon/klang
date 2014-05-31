#include "kobject.h"

class FuncPrint : public KFunction {
    KObject* invoke(std::vector<KObject*> args);
	virtual FuncPrint *clone() const { return new FuncPrint(*this); }
};
