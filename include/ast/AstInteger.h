#pragma once

#include "kobject/KInteger.h"
#include "Binding.h"

#include "ast/AstNumber.h"

class AstInteger : public AstNumber {
public:
    long value;

	virtual KInteger *evaluate(Binding *b);

    virtual void save_value();
};
