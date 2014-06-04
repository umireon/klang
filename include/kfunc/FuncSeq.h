#pragma once

#include <vector>

#include "kobject/KObject.h"
#include "kobject/KFunction.h"

class FuncSeq : public KFunction {
public:
    KObject *invoke(std::vector<KObject*> args);
    KVector *invoke(KNumber *first, KNumber *last);
	virtual FuncSeq *clone() const { return new FuncSeq(*this); }
};
