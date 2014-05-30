#include "kobject.h"

class FuncMatrix : public KFunction {
    KObject* invoke(std::vector<KObject*> args);
	virtual FuncMatrix *clone() const { return new FuncMatrix(*this); }
};
