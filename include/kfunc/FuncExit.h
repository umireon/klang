#include "kobject.h"

class FuncExit : public KFunction {
    KObject* invoke(std::vector<KObject*> args);
	virtual FuncExit *clone() const { return new FuncExit(*this); }
};
