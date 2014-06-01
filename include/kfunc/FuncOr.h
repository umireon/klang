#pragma once

#include <vector>

#include "kobject/KObject.h"
#include "kobject/KFunction.h"

class FuncOr : public KFunction {
public:
    KObject *invoke(std::vector<KObject*> args);
	virtual FuncOr *clone() const { return new FuncOr(*this); }
};
