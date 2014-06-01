#pragma once

#include <vector>

#include "kobject/KObject.h"

class KFunction : public KObject {
public:
    virtual enum Type get_type() { return FUNCTION; }
    virtual std::string to_s() { return std::string("Function"); }
	virtual KFunction *clone() const = 0;

	virtual KObject *invoke(std::vector<KObject*> args) = 0;
};
