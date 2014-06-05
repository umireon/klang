#pragma once

#include <vector>

#include "kobject/KObject.h"

class FuncMath : public KFunction {
public:
	double (*mathfunc)(double);

	FuncMath(double (*mathfunc)(double)) : mathfunc(mathfunc) {}
    KObject *invoke(std::vector<KObject*> args);
	virtual FuncMath *clone() const { return new FuncMath(*this); }
};
