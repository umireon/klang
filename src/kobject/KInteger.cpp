#include <string>
#include <sstream>
#include <stdexcept>

#include "kobject.h"

using namespace boost::numeric;

KObject* KInteger::op_add(KObject *right)
{
	switch (right->get_type()) {
		case INTEGER:
			return op_add(static_cast<KInteger *>(right));
		case FLOAT:
		case VECTOR:
			return right->op_add(this);
			break;
		default:
			throw std::invalid_argument(std::string("Unsupported RHS"));
	}
}

KObject* KInteger::op_sub(KObject *right)
{
	switch (right->get_type()) {
		case INTEGER:
			return op_sub(static_cast<KInteger *>(right));
		case FLOAT:
			return op_sub(static_cast<KFloat *>(right));
		case VECTOR:
			return op_sub(static_cast<KVector *>(right));
			break;
		default:
			throw std::invalid_argument(std::string("Unsupported RHS"));
	}
}

KObject* KInteger::op_mul(KObject *right)
{
	switch (right->get_type()) {
		case INTEGER:
			return op_mul(static_cast<KInteger *>(right));
		case FLOAT:
		case VECTOR:
			return right->op_mul(this);
			break;
		default:
			throw std::invalid_argument(std::string("Unsupported RHS"));
	}
}

KObject* KInteger::op_div(KObject *right)
{
	switch (right->get_type()) {
		case INTEGER:
			return op_div(static_cast<KInteger *>(right));
		case FLOAT:
			return op_div(static_cast<KFloat *>(right));
		case VECTOR:
			return op_div(static_cast<KVector *>(right));
			break;
		default:
			throw std::invalid_argument(std::string("Unsupported RHS"));
	}
}

KObject* KInteger::op_rem(KObject *right)
{
	switch (right->get_type()) {
		case INTEGER:
		case FLOAT:
			return op_rem(static_cast<KNumber *>(right));
		case VECTOR:
			return right->op_rem(this);
			break;
		default:
			throw std::invalid_argument(std::string("Unsupported RHS"));
	}
}

KObject* KInteger::op_pow(KObject *right)
{
	switch (right->get_type()) {
		case INTEGER:
			return op_pow(static_cast<KInteger *>(right));
		case FLOAT:
			return op_pow(static_cast<KFloat *>(right));
		case VECTOR:
			return right->op_pow(this);
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

KInteger* KInteger::op_sub(KInteger *right)
{
	long newValue = value - right->to_i();
	return new KInteger(newValue);
}

KFloat* KInteger::op_sub(KFloat *right)
{
	double newValue = value - right->to_f();
	return new KFloat(newValue);
}

KVector* KInteger::op_sub(KVector *right)
{
	dscalar_vector r(right->vect.size(), to_f());
	dvector newValue = r - right->vect;
	KVector *kvect = new KVector(newValue);
	return kvect;
}

KInteger* KInteger::op_mul(KInteger *right)
{
	long newValue = value * right->to_i();
	return new KInteger(newValue);
}

KInteger* KInteger::op_div(KInteger *right)
{
	long newValue = value / right->to_i();
	return new KInteger(newValue);
}

KFloat* KInteger::op_div(KFloat *right)
{
	double newValue = value / right->to_f();
	return new KFloat(newValue);
}

KVector* KInteger::op_div(KVector *right)
{
	dscalar_vector r(right->vect.size(), value);
	dvector newValue = element_div(r, right->vect);
	return new KVector(newValue);
}

KInteger* KInteger::op_rem(KNumber *right)
{
	long newValue = value % right->to_i();
	return new KInteger(newValue);
}

KInteger* KInteger::op_pow(KInteger *right)
{
    long base = value;
    long num = right->to_i();
    long value = 1;
    for (int i = 0; i < num; i++) {
        value *= base;
    }
    return new KInteger(value);
}

KFloat* KInteger::op_pow(KFloat *right)
{
	double newValue = pow(value, right->to_f());
	return new KFloat(newValue);
}
