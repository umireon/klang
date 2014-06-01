#pragma once

#include <vector>

#include "kobject/KObject.h"

class FuncPuts : public KFunction {
public:
    FuncPuts(std::ostream &os) : output(os) {}

    KObject *invoke(std::vector<KObject*> args);
	virtual FuncPuts *clone() const { return new FuncPuts(*this); }

private:
    std::ostream &output;
};
