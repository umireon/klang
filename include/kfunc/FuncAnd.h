#pragma once

#include <vector>

#include "kobject/KObject.h"
#include "kobject/KFunction.h"

class FuncAnd : public KFunction {
public:
    KObject *invoke(std::vector<KObject*> args);
	virtual FuncAnd *clone() const { return new FuncAnd(*this); }
};
