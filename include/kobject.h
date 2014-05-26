#pragma once

#include <map>

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>

using namespace boost::numeric;

typedef boost::numeric::ublas::matrix<double> dmatrix;
typedef boost::numeric::ublas::vector<double> dvector;

class KObject {
public:
	virtual std::string to_string() { return std::string("Object"); }
	virtual std::string to_s() { return std::string("Object"); }
};

class KVector : public KObject {
public:
    ublas::vector<double> vect;
	virtual std::string to_string() { return std::string("Vector"); }
    std::string to_s();
};

class KMatrix : public KObject {
public:
    ublas::matrix<double> mat;
	virtual std::string to_string() { return std::string("Matrix"); }
    std::string to_s();
};

class KNumber : public KObject {
public:
	enum Type {
		INTEGER,
		FLOAT
	};
    
	enum Type type;
    
	virtual ~KNumber() {}
	virtual std::string to_string() { return std::string("Number"); }
	virtual long to_i() = 0;
	virtual double to_f() = 0;
};

class KInteger : public KNumber {
public:
	long value;
    
	KInteger(long v) { type = INTEGER; value = v; }
	long to_i() { return value; }
	double to_f() { return value; }
	std::string to_string() { return std::string("Integer"); }
};

class KFloat : public KNumber {
public:
	double value;
    
	KFloat(double v) { type = FLOAT; value = v; }
	long to_i() { return value; }
	double to_f() { return value; }
	std::string to_string() { return std::string("Float"); }
};

class KFunction : public KObject {
public:
	virtual KObject* invoke(std::vector<KObject*> args) = 0;
	std::string to_string() { return std::string("Function"); }
};
