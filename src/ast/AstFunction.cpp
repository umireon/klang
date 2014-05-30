#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>

#include "ast/AstFunction.h"

AstFunction::~AstFunction(void)
{
	delete astParam;
	delete body;
	delete identName;
}

KFunctionAst* AstFunction::evaluate(Binding *b)
{
	std::vector<AstIdentifier *> &params = astParam->params;
	std::vector<AstIdentifier *>::iterator iter = params.begin();

	std::vector<std::string> paramNames;

	while (iter != params.end()) {
		AstIdentifier *ident = *iter;

		if (ident->get_identifier_type() == AstIdentifier::NAME) {
			paramNames.push_back(ident->get_string());
		} else {
            std::ostringstream os;
            os << "Reserved word for Parameter: " << ident->get_string() << std::endl;
            throw std::invalid_argument(os.str());
		}

		iter++;
	}

	KFunctionAst *f = new KFunctionAst(body, paramNames);

	if (identName != NULL) {
		if (identName->get_identifier_type() != AstIdentifier::NAME) {
	        std::ostringstream os;
	        os << "Reserved word for Parameter: " << identName->get_string() << std::endl;
	        throw std::invalid_argument(os.str());
		}

		b->set_local(identName->get_string(), f);
	}

	return f;
}
