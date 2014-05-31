#pragma once

#include "kobject.h"
#include "Binding.h"
#include "ast/AstNumber.h"

class AstInteger : public AstNumber {
public:
	virtual KInteger *evaluate(Binding *b);
};
