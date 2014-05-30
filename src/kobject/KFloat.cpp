#include <string>
#include <sstream>
#include <stdexcept>

#include "kobject.h"

using namespace boost::numeric;

KObject* KFloat::op_add(KObject *right)
{
	switch (right->get_type()) {
		case INTEGER:
		case FLOAT:
			return op_add(static_cast<KNumber *>(right));
		case VECTOR:
			return right->op_add(this);
		default:
			throw std::invalid_argument(std::string("Unsupported RHS"));
	}
}

KObject* KFloat::op_sub(KObject *right)
{
	switch (right->get_type()) {
		case INTEGER:
		case FLOAT:
			return op_sub(static_cast<KNumber *>(right));
		case VECTOR:
			return op_sub(static_cast<KVector *>(right));
		default:
			throw std::invalid_argument(std::string("Unsupported RHS"));
	}
}

KObject* KFloat::op_mul(KObject *right)
{
	switch (right->get_type()) {
		case INTEGER:
		case FLOAT:
			return op_mul(static_cast<KNumber *>(right));
		case VECTOR:
			return right->op_mul(this);
		default:
			throw std::invalid_argument(std::string("Unsupported RHS"));
	}
}

KObject* KFloat::op_div(KObject *right)
{
	switch (right->get_type()) {
		case INTEGER:
		case FLOAT:
			return op_div(static_cast<KNumber *>(right));
		case VECTOR:
			return op_div(static_cast<KVector *>(right));
		default:
			throw std::invalid_argument(std::string("Unsupported RHS"));
	}
}

KObject* KFloat::op_rem(KObject *right)
{
	switch (right->get_type()) {
		case INTEGER:
		case FLOAT:
			return op_rem(static_cast<KNumber *>(right));
		case VECTOR:
			return right->op_rem(this);
		default:
			throw std::invalid_argument(std::string("Unsupported RHS"));
	}
}

KObject* KFloat::op_pow(KObject *right)
{
	switch (right->get_type()) {
		case INTEGER:
		case FLOAT:
			return op_pow(static_cast<KNumber *>(right));
		case VECTOR:
			return right->op_pow(this);
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

KFloat* KFloat::op_add(KNumber *right)
{
	double newValue = value + right->to_f();
	return new KFloat(newValue);
}

KFloat* KFloat::op_sub(KNumber *right)
{
	double newValue = value - right->to_f();
	return new KFloat(newValue);
}

KVector* KFloat::op_sub(KVector *right)
{
	dscalar_vector r(right->vect.size(), value);
	dvector newValue = r - right->vect;
	KVector *kvect = new KVector(newValue);
	return kvect;
}

KFloat* KFloat::op_mul(KNumber *right)
{
	double newValue = value * right->to_f();
	return new KFloat(newValue);
}

KFloat* KFloat::op_div(KNumber *right)
{
	double newValue = value / right->to_f();
	return new KFloat(newValue);
}

KVector* KFloat::op_div(KVector *right)
{
	dscalar_vector r(right->vect.size(), value);
	dvector newValue = element_div(r, right->vect);
	return new KVector(newValue);
}

KInteger* KFloat::op_rem(KNumber *right)
{
	int newValue = static_cast<long>(value) % right->to_i();
	return new KInteger(newValue);
}

KFloat* KFloat::op_pow(KNumber *right)
{
	double newValue = pow(value, right->to_f());
	return new KFloat(newValue);
}
