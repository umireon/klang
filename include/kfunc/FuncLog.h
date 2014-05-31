#include "kobject.h"

class FuncLog : public KFunction {
    KObject* invoke(std::vector<KObject*> args);
	virtual FuncLog *clone() const { return new FuncLog(*this); }
};
