#include <sstream>
#include <stdexcept>

#include "kobject.h"

#include "ast/AstIdentifier.h"

KObject* AstIdentifier::evaluate(Binding* b)
{
    std::string name = get_string();
    return b->get_local(name);
}

AstIdentifier::IdentifierType AstIdentifier::get_identifier_type()
{
	std::string s(get_string());
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
