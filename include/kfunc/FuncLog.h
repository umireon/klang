#pragma once

#include <vector>

#include "kobject/KObject.h"

class FuncLog : public KFunction {
    KObject *invoke(std::vector<KObject*> args);
	virtual FuncLog *clone() const { return new FuncLog(*this); }
};
