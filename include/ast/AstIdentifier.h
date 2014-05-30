#pragma once

#include <string>

#include "kobject.h"

class AstIdentifier : public AstNode {
public:
	enum IdentifierType {
		NAME,
		FUNCTION
	};

	virtual KObject* evaluate(Binding* b);
	std::string get_name();
	IdentifierType get_identifier_type();
};