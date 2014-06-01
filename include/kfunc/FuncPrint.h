#pragma once

#include <vector>

#include "kobject/KObject.h"

class FuncPrint : public KFunction {
    KObject *invoke(std::vector<KObject*> args);
	virtual FuncPrint *clone() const { return new FuncPrint(*this); }
};
