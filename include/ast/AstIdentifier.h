#pragma once

#include <string>

#include "kobject.h"
#include "Binding.h"
#include "ast/AstNode.h"

class AstIdentifier : public AstNode {
public:
	enum IdentifierType {
		NAME,
		FUNCTION,
        IF,
        ELSE,
        ELSIF
	};

	virtual KObject *evaluate(Binding *b);
	std::string get_name();
	IdentifierType get_identifier_type();
};
