#pragma once

#include <vector>

#include "Binding.h"
#include "ast/AstNode.h"

class KTrue : public KObject {
public:
    enum Type get_type() { return NIL; }
    std::string to_s() { return std::string("nil"); }
	virtual KNil *clone() const { return new KNil(*this); }
};
