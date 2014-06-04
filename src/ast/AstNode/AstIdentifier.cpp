#include "kobject/KObject.h"
#include "Binding.h"

#include "ast/AstIdentifier.h"

KObject* AstIdentifier::evaluate(Binding* b)
{
    return b->get_local(value);
}

std::string AstIdentifier::get_name()
{
    return value;
}

AstIdentifier::IdentifierType AstIdentifier::get_identifier_type()
{
	std::string s(get_name());
	if (s == std::string("function")) {
		return FUNCTION;
    } else if (s == std::string("if")) {
        return IF;
    } else if (s == std::string("else")) {
        return ELSE;
    } else if (s == std::string("elsif")) {
        return ELSIF;
	} else {
		return NAME;
	}
}
