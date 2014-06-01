#pragma once

#include <vector>

#include "kobject/KObject.h"

class FuncExit : public KFunction {
    KObject *invoke(std::vector<KObject*> args);
	virtual FuncExit *clone() const { return new FuncExit(*this); }
};
