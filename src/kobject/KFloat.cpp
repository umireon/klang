#include <string>
#include <sstream>
#include <stdexcept>

#include "kobject.h"

using namespace boost::numeric;

KFloat* KFloat::op_mul(KNumber *right)
{
	double newValue = value * right->to_f();
	return new KFloat(newValue);
}

KObject* KFloat::op_mul(KObject *right)
{
	switch (right->type) {
		case INTEGER:
		case FLOAT:
			return op_mul(static_cast<KNumber*>(right));
		case VECTOR:
			return right->op_mul(this);
		default:
			throw std::invalid_argument(std::string("Unsupported RHS"));
	}
}

std::string KFloat::to_s(void)
{
    std::ostringstream os;
    os << value;
    return std::string(os.str());
}
