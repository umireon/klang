#include <string>
#include <sstream>

#include <boost/numeric/ublas/vector.hpp>

#include "kobject.h"

using namespace boost::numeric;

KVector* KVector::op_mul(KNumber *right)
{
	dvector newValue = vect * right->to_f();
	KVector *kvect = new KVector();
	kvect->vect = newValue;
	return kvect;
}

KFloat* KVector::op_mul(KVector *right)
{
	double newValue = inner_prod(vect, right->vect);
	KFloat *kflt = new KFloat(newValue);
	return kflt;
}

KObject* KVector::op_mul(KObject *right)
{
	switch (right->type) {
		case INTEGER:
		case FLOAT:
			return op_mul(static_cast<KNumber*>(right));
			break;
		case VECTOR:
			return op_mul(static_cast<KVector*>(right));
			break;
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


