#pragma once

#include "kobject/KInteger.h"
#include "Binding.h"

#include "ast/AstNumber.h"

class AstInteger : public AstNumber {
public:
	virtual KInteger *evaluate(Binding *b);
};
