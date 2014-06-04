#pragma once

#include <vector>

#include "kobject/KObject.h"
#include "kobject/KFunction.h"

class FuncProd : public KFunction {
public:
    KObject *invoke(std::vector<KObject*> args);
	virtual FuncProd *clone() const { return new FuncProd(*this); }
};
