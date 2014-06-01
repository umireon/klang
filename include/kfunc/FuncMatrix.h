#pragma once

#include <vector>

#include "kobject/KObject.h"

class FuncMatrix : public KFunction {
    KObject *invoke(std::vector<KObject*> args);
	virtual FuncMatrix *clone() const { return new FuncMatrix(*this); }
};
