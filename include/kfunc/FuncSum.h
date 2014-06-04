#pragma once

#include <vector>

#include "kobject/KObject.h"
#include "kobject/KFunction.h"

class FuncSum : public KFunction {
public:
    KObject *invoke(std::vector<KObject*> args);
	virtual FuncSum *clone() const { return new FuncSum(*this); }
};