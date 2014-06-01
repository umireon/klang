#pragma once

#include <boost/numeric/ublas/vector.hpp>

#include "kobject/KObject.h"
#include "kobject/KNumber.h"
#include "kobject/KVector.h"

typedef boost::numeric::ublas::vector<double> dvector;
typedef boost::numeric::ublas::scalar_vector<double> dscalar_vector;

class KVector : public KObject {
public:
    dvector vect;

	KVector(dvector v) : vect(v) {}

    virtual enum Type get_type() { return VECTOR; }
	virtual KObject *op_add(KObject *right);
	virtual KObject *op_sub(KObject *right);
	virtual KObject *op_mul(KObject *right);
	virtual KObject *op_div(KObject *right);
	virtual KObject *op_rem(KObject *right);
	virtual KObject *op_pow(KObject *right);
    virtual std::string to_s();
	virtual KVector *clone() const { return new KVector(*this); }

	KVector *op_add(KNumber* right);
	KVector *op_add(KVector *right);
	KVector *op_sub(KNumber* right);
	KVector *op_sub(KVector *right);
	KVector *op_mul(KNumber* right);
	KVector *op_mul(KVector *right);
	KVector *op_div(KNumber* right);
	KVector *op_div(KVector *right);
	KVector *op_rem(KNumber* right);
	KVector *op_pow(KNumber* right);
	KVector *op_pow(KVector *right);
};
