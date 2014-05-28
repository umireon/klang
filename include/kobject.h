#pragma once

#include <map>

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>

typedef boost::numeric::ublas::matrix<double> dmatrix;
typedef boost::numeric::ublas::vector<double> dvector;

using namespace boost::numeric;

class KObject {
public:
	enum Type {
		INTEGER,
		FLOAT,
		VECTOR,
		MATRIX,
        FUNCTION
	};

    virtual enum Type get_type() = 0;
	virtual KObject* op_mul(KObject* right) { throw std::invalid_argument(std::string("op_mul is not defined."));}
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
	virtual KObject* op_mul(KObject* right);
    virtual std::string to_s();

	virtual long to_i() { return value; }
	virtual double to_f() { return static_cast<double>(value); }

	KInteger* op_mul(KInteger* right);
private:
	long value;
};

class KFloat : public KNumber {
public:
	KFloat(double v) : value(v) {}
    
    enum Type get_type() { return FLOAT; }
	KObject* op_mul(KObject* right);
    std::string to_s();

	long to_i() { return static_cast<long>(value); }
	double to_f() { return value; }

	KFloat* op_mul(KNumber* right);
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
