#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>

#include "ast/AstFunction.h"

AstFunction::~AstFunction(void)
{
	delete astParam;
	delete body;
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

	return new KFunctionAst(b, body, paramNames);
}
