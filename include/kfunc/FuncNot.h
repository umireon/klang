#pragma once

#include <vector>

#include "kobject/KObject.h"
#include "kobject/KFunction.h"

class FuncNot : public KFunction {
public:
    KObject *invoke(std::vector<KObject*> args);
	virtual FuncNot *clone() const { return new FuncNot(*this); }
};
