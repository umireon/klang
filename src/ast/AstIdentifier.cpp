#include <sstream>
#include <stdexcept>

#include "kobject.h"

#include "ast.h"

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
	} else {
		return NAME;
	}
}
