#include <string>
#include <sstream>
#include <stdexcept>

#include "kobject.h"

using namespace boost::numeric;

KObject* KInteger::op_add(KObject *right)
{
	switch (right->get_type()) {
		case INTEGER:
			return op_add(static_cast<KInteger*>(right));
		case FLOAT:
		case VECTOR:
			return right->op_mul(this);
			break;
		default:
			throw std::invalid_argument(std::string("Unsupported RHS"));
	}
}

KObject* KInteger::op_mul(KObject *right)
{
	switch (right->get_type()) {
		case INTEGER:
			return op_mul(static_cast<KInteger*>(right));
		case FLOAT:
		case VECTOR:
			return right->op_mul(this);
			break;
		default:
			throw std::invalid_argument(std::string("Unsupported RHS"));
	}
}

std::string KInteger::to_s(void)
{
    std::ostringstream os;
    os << value;
    return std::string(os.str());
}

KInteger* KInteger::op_add(KInteger *right)
{
	long newValue = value + right->to_i();
	return new KInteger(newValue);
}

KInteger* KInteger::op_mul(KInteger *right)
{
	long newValue = value * right->to_i();
	return new KInteger(newValue);
}
