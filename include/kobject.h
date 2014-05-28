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
		MATRIX
	};

	enum Type type;
    
    KObject(enum Type t) : type(t) {};

	virtual KObject* op_mul(KObject* right) = 0;
	virtual std::string to_s() { return std::string("Object"); }
};

class KNumber : public KObject {
public:
    KNumber(enum Type t) : KObject(t) {};
	virtual ~KNumber() {}
	virtual long to_i() = 0;
	virtual double to_f() = 0;
};

class KInteger : public KNumber {
public:
    KInteger() : KNumber(INTEGER) {};
	KInteger(long v) : KNumber(INTEGER), value(v) {};
    KInteger(KInteger &kint) : KInteger(kint.value) {};

	KInteger* op_mul(KInteger* right);
	KObject* op_mul(KObject* right);
	long to_i() { return value; }
	double to_f() { return static_cast<double>(value); }
    std::string to_s();
private:
	long value;
};

class KFloat : public KNumber {
public:
	KFloat(double v) { type = FLOAT; value = v; }

	KFloat* op_mul(KNumber* right);
	KObject* op_mul(KObject* right);
	long to_i() { return static_cast<long>(value); }
	double to_f() { return value; }
    std::string to_s();
private:
	double value;
};

class KVector : public KObject {
public:
	KVector() { type = VECTOR; }

	KVector* op_mul(KNumber* right);
	KFloat* op_mul(KVector* right);
	KObject* op_mul(KObject* right);

    dvector vect;
    std::string to_s();
};

class KMatrix : public KObject {
public:
	KMatrix() { type = MATRIX; }

    ublas::matrix<double> mat;
    std::string to_s();
};

class KFunction : public KObject {
public:
	virtual KObject* invoke(std::vector<KObject*> args) = 0;
};
