#pragma once

#include <vector>

#include "kobject/KObject.h"

class FuncPuts : public KFunction {
    KObject *invoke(std::vector<KObject*> args);
	virtual FuncPuts *clone() const { return new FuncPuts(*this); }
};
