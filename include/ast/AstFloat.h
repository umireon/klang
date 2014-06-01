#pragma once

#include "kobject/KFloat.h"
#include "Binding.h"
#include "ast/AstNumber.h"

class AstFloat : public AstNumber {
public:
    double value;

	virtual KFloat *evaluate(Binding *b);
    
    virtual void save_value();
};
