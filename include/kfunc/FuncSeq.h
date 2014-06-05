#pragma once

#include <iostream>
#include <vector>

#include "kobject/KObject.h"
#include "kobject/KFunction.h"

class FuncSeq : public KFunction {
public:
    FuncSeq() : outerror(std::cerr) {}
    FuncSeq(std::ostream &os) : outerror(os) {}

    KObject *invoke(std::vector<KObject*> args);
    KVector *invoke(KNumber *first, KNumber *last);
	virtual FuncSeq *clone() const { return new FuncSeq(*this); }

private:
    std::ostream &outerror;
};
