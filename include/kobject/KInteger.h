#pragma once

class KFloat;

#include "kobject/KObject.h"
#include "kobject/KNumber.h"
#include "kobject/KFloat.h"
#include "kobject/KVector.h"

class KInteger : public KNumber {
public:
	long value;

	KInteger(long v) : value(v) {};

    virtual enum Type get_type() { return INTEGER; }
	virtual KObject *op_add(KObject *right);
	virtual KObject *op_sub(KObject *right);
	virtual KObject *op_mul(KObject *right);
	virtual KObject *op_div(KObject *right);
	virtual KObject *op_rem(KObject *right);
	virtual KObject *op_pow(KObject *right);
    virtual std::string to_s();
	virtual KInteger *clone() const { return new KInteger(*this); }

	virtual long to_i() { return value; }
	virtual double to_f() { return static_cast<double>(value); }

	KInteger *op_add(KInteger *right);
	KInteger *op_sub(KInteger *right);
	KFloat *op_sub(KFloat *right);
	KVector *op_sub(KVector *right);
	KInteger *op_mul(KInteger *right);
	KInteger *op_div(KInteger *right);
	KFloat *op_div(KFloat *right);
	KVector *op_div(KVector *right);
	KInteger *op_rem(KNumber* right);
	KInteger *op_pow(KInteger *right);
	KFloat *op_pow(KFloat *right);
	KVector *op_pow(KVector *right);
};
