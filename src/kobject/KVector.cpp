#include <string>
#include <sstream>

#include <boost/numeric/ublas/vector.hpp>

#include "kobject.h"

using namespace boost::numeric;

KObject* KVector::op_add(KObject *right)
{
	switch (right->get_type()) {
		case INTEGER:
		case FLOAT:
			return op_add(static_cast<KNumber*>(right));
		case VECTOR:
			return op_add(static_cast<KVector*>(right));
		default:
			throw std::invalid_argument(std::string("Unsupported RHS"));
	}
}

KObject* KVector::op_sub(KObject *right)
{
	switch (right->get_type()) {
		case INTEGER:
		case FLOAT:
			return op_sub(static_cast<KNumber*>(right));
		case VECTOR:
			return op_sub(static_cast<KVector*>(right));
		default:
			throw std::invalid_argument(std::string("Unsupported RHS"));
	}
}

KObject* KVector::op_mul(KObject *right)
{
	switch (right->get_type()) {
		case INTEGER:
		case FLOAT:
			return op_mul(static_cast<KNumber*>(right));
		case VECTOR:
			return op_mul(static_cast<KVector*>(right));
		default:
			throw std::invalid_argument(std::string("Unsupported RHS"));
	}
}

KObject* KVector::op_div(KObject *right)
{
	switch (right->get_type()) {
		case INTEGER:
		case FLOAT:
			return op_div(static_cast<KNumber*>(right));
		case VECTOR:
			return op_div(static_cast<KVector*>(right));
		default:
			throw std::invalid_argument(std::string("Unsupported RHS"));
	}
}

KObject* KVector::op_rem(KObject *right)
{
	switch (right->get_type()) {
		case INTEGER:
		case FLOAT:
			return op_rem(static_cast<KNumber*>(right));
		default:
			throw std::invalid_argument(std::string("Unsupported RHS"));
	}
}

KObject* KVector::op_pow(KObject *right)
{
	switch (right->get_type()) {
		case INTEGER:
		case FLOAT:
			return op_pow(static_cast<KNumber*>(right));
		case VECTOR:
			return op_pow(static_cast<KVector*>(right));
		default:
			throw std::invalid_argument(std::string("Unsupported RHS"));
	}
}

std::string KVector::to_s(void)
{
    std::ostringstream os;
    os << "[ ";
    
    ublas::vector<double>::iterator iter = vect.begin();
    
    while (iter != vect.end()) {
        os << *iter << " ";
        iter++;
    }
    
    os << "]";

    return std::string(os.str());
}

KVector* KVector::op_add(KNumber *right)
{
	dscalar_vector r(vect.size(), right->to_f());
	dvector newValue = vect + r;
	KVector *kvect = new KVector(newValue);
	return kvect;
}

KVector* KVector::op_add(KVector *right)
{
	return new KVector(vect + right->vect);
}

KVector* KVector::op_sub(KNumber *right)
{
	dscalar_vector r(vect.size(), right->to_f());
	dvector newValue = vect - r;
	KVector *kvect = new KVector(newValue);
	return kvect;
}

KVector* KVector::op_sub(KVector *right)
{
	return new KVector(vect - right->vect);
}

KVector* KVector::op_mul(KNumber *right)
{
	dvector newValue = vect * right->to_f();
	KVector *kvect = new KVector(newValue);
	return kvect;
}

KVector* KVector::op_mul(KVector *right)
{
	dvector newValue = element_prod(vect, right->vect);
	return new KVector(newValue);
}

KVector* KVector::op_div(KNumber *right)
{
	dvector newValue = vect / right->to_f();
	KVector *kvect = new KVector(newValue);
	return kvect;
}

KVector* KVector::op_div(KVector *right)
{
	dvector newValue = element_div(vect, right->vect);
	return new KVector(newValue);
}

KVector* KVector::op_rem(KNumber *right)
{
	dvector newValue(vect.size());

    for (int i = 0; i < newValue.size(); i++) {
        newValue[i] = (long)vect[i] % right->to_i();
    }

	return new KVector(newValue);
}

KVector* KVector::op_pow(KNumber *right)
{
	dvector newValue(vect.size());
	double e = right->to_f();

    for (int i = 0; i < newValue.size(); i++) {
        newValue[i] = pow(vect[i], e);
    }

	return new KVector(newValue);
}

KVector* KVector::op_pow(KVector *right)
{
	dvector &rvect = right->vect;
	dvector newValue(vect.size());

    for (int i = 0; i < newValue.size(); i++) {
        newValue[i] = pow(vect[i], rvect[i]);
    }

	return new KVector(newValue);
}
