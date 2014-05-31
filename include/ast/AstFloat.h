#pragma once

#include "kobject.h"
#include "Binding.h"
#include "ast/AstNumber.h"

class AstFloat : public AstNumber {
public:
	virtual KFloat *evaluate(Binding *b);
};
