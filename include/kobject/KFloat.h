#pragma once

class KInteger;

#include "kobject/KObject.h"
#include "kobject/KNumber.h"
#include "kobject/KInteger.h"
#include "kobject/KVector.h"

class KFloat : public KNumber {
public:
	double value;

	KFloat(double v) : value(v) {}
    
    enum Type get_type() { return FLOAT; }
	virtual KObject *op_add(KObject *right);
	virtual KObject *op_sub(KObject *right);
	virtual KObject *op_mul(KObject *right);
	virtual KObject *op_div(KObject *right);
	virtual KObject *op_rem(KObject *right);
	virtual KObject *op_pow(KObject *right);
    virtual std::string to_s();
	virtual KFloat *clone() const { return new KFloat(*this); }

	long to_i() { return static_cast<long>(value); }
	double to_f() { return value; }

	KFloat *op_add(KNumber* right);
	KFloat *op_sub(KNumber* right);
	KVector *op_sub(KVector *right);
	KFloat *op_mul(KNumber* right);
	KFloat *op_div(KNumber* right);
	KVector *op_div(KVector *right);
	KInteger *op_rem(KNumber* right);
	KFloat *op_pow(KNumber* right);
	KVector *op_pow(KVector *right);
};
