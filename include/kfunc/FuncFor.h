#pragma once

#include <vector>

#include "kobject/KObject.h"

class FuncFor : public KFunction {
    KObject *invoke(std::vector<KObject*> args);
	virtual FuncFor *clone() const { return new FuncFor(*this); }

	KObject *invoke(KVector *kvect, KFunction *kfunc);
};
