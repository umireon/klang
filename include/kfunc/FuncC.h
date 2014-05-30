#include "kobject.h"

class FuncC : public KFunction {
    KObject* invoke(std::vector<KObject*> args);
	virtual FuncC *clone() const { return new FuncC(*this); }
};
