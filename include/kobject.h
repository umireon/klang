#pragma once

#include <map>

#include <boost/numeric/ublas/vector.hpp>

typedef boost::numeric::ublas::vector<double> dvector;
typedef boost::numeric::ublas::scalar_vector<double> dscalar_vector;

using namespace boost::numeric;

class KInteger;
class KFloat;
class KVector;

class KObject {
public:
	enum Type {
		INTEGER,
		FLOAT,
		VECTOR,
		MATRIX,
        FUNCTION,
        NIL,
	};

	virtual ~KObject() {}

    virtual enum Type get_type() = 0;
	virtual KObject *op_add(KObject *right) { throw std::invalid_argument(std::string("op_add is not defined."));}
	virtual KObject *op_sub(KObject *right) { throw std::invalid_argument(std::string("op_sub is not defined."));}
	virtual KObject *op_mul(KObject *right) { throw std::invalid_argument(std::string("op_mul is not defined."));}
	virtual KObject *op_div(KObject *right) { throw std::invalid_argument(std::string("op_div is not defined."));}
	virtual KObject *op_rem(KObject *right) { throw std::invalid_argument(std::string("op_rem is not defined."));}
	virtual KObject *op_pow(KObject *right) { throw std::invalid_argument(std::string("op_pow is not defined."));}
	virtual std::string to_s() { return std::string("Object"); }
	virtual KObject *clone() const = 0;
};

class KNumber : public KObject {
public:
	virtual ~KNumber() {}
	virtual long to_i() = 0;
	virtual double to_f() = 0;
};

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

class KFunction : public KObject {
public:
    virtual enum Type get_type() { return FUNCTION; }
    virtual std::string to_s() { return std::string("Function"); }
	virtual KFunction *clone() const = 0;

	virtual KObject *invoke(std::vector<KObject*> args) = 0;
};

