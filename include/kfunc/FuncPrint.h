#pragma once

#include <iostream>
#include <vector>

#include "kobject/KObject.h"

class FuncPrint : public KFunction {
public:
    FuncPrint(std::ostream &os) : output(os) {}

    KObject *invoke(std::vector<KObject*> args);
	virtual FuncPrint *clone() const { return new FuncPrint(*this); }

private:
    std::ostream &output;
};
