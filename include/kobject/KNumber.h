#pragma once

#include "kobject/KObject.h"

class KNumber : public KObject {
public:
	virtual ~KNumber() {}
	virtual long to_i() = 0;
	virtual double to_f() = 0;
};
