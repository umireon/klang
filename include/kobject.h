#pragma once

#include <map>

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>

typedef boost::numeric::ublas::matrix<double> dmatrix;
typedef boost::numeric::ublas::vector<double> dvector;

using namespace boost::numeric;

class KFloat;

class KObject {
public:
	enum Type {
		INTEGER,
		FLOAT,
		VECTOR,
		MATRIX,
        FUNCTION
	};

	virtual ~KObject() {}

    virtual enum Type get_type() = 0;
	virtual KObject* op_add(KObject* right) { throw std::invalid_argument(std::string("op_add is not defined."));}
	virtual KObject* op_sub(KObject* right) { throw std::invalid_argument(std::string("op_sub is not defined."));}
	virtual KObject* op_mul(KObject* right) { throw std::invalid_argument(std::string("op_mul is not defined."));}
	virtual KObject* op_div(KObject* right) { throw std::invalid_argument(std::string("op_div is not defined."));}
	virtual KObject* op_rem(KObject* right) { throw std::invalid_argument(std::string("op_rem is not defined."));}
	virtual std::string to_s() { return std::string("Object"); }
};

class KNumber : public KObject {
public:
	virtual ~KNumber() {}
	virtual long to_i() = 0;
	virtual double to_f() = 0;
};

class KInteger : public KNumber {
public:
	KInteger(long v) : value(v) {};

    virtual enum Type get_type() { return INTEGER; }
	virtual KObject* op_add(KObject* right);
	virtual KObject* op_sub(KObject* right);
	virtual KObject* op_mul(KObject* right);
	virtual KObject* op_div(KObject* right);
	virtual KObject* op_rem(KObject* right);
    virtual std::string to_s();

	virtual long to_i() { return value; }
	virtual double to_f() { return static_cast<double>(value); }

	KInteger* op_add(KInteger* right);
	KInteger* op_sub(KInteger* right);
	KFloat* op_sub(KFloat* right);
	KInteger* op_mul(KInteger* right);
	KInteger* op_div(KInteger* right);
	KFloat* op_div(KFloat* right);
	KInteger* op_rem(KNumber* right);
private:
	long value;
};

class KFloat : public KNumber {
public:
	KFloat(double v) : value(v) {}
    
    enum Type get_type() { return FLOAT; }
	virtual KObject* op_add(KObject* right);
	virtual KObject* op_sub(KObject* right);
	virtual KObject* op_mul(KObject* right);
	virtual KObject* op_div(KObject* right);
	virtual KObject* op_rem(KObject* right);
    virtual std::string to_s();

	long to_i() { return static_cast<long>(value); }
	double to_f() { return value; }

	KFloat* op_add(KNumber* right);
	KFloat* op_sub(KNumber* right);
	KFloat* op_mul(KNumber* right);
	KFloat* op_div(KNumber* right);
	KInteger* op_rem(KNumber* right);
private:
	double value;
};

class KVector : public KObject {
public:
    dvector vect;

	KVector(dvector v) : vect(v) {}

    enum Type get_type() { return VECTOR; }
	KObject* op_mul(KObject* right);
    std::string to_s();

	KVector* op_mul(KNumber* right);
	KVector* op_mul(KVector* right);
};

class KMatrix : public KObject {
public:
    dmatrix mat;

    KMatrix(dmatrix m) : mat(m) {};
    
    enum Type get_type() { return MATRIX; }
	KObject* op_mul(KObject* right) { return NULL; };
    std::string to_s();
};

class KFunction : public KObject {
public:
    enum Type get_type() { return FUNCTION; }
    std::string to_s() { return std::string("Function"); }

	virtual KObject* invoke(std::vector<KObject*> args) = 0;
};
