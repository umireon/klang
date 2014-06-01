#pragma once

#include "kobject.h"
#include <boost/numeric/ublas/matrix.hpp>

typedef boost::numeric::ublas::matrix<double> dmatrix;

class KMatrix : public KObject {
public:
    dmatrix mat;

    KMatrix(dmatrix m) : mat(m) {};
    
    virtual enum Type get_type() { return MATRIX; }
	virtual KObject *op_mul(KObject *right) { return NULL; };
    virtual std::string to_s();
	virtual KMatrix *clone() const { return new KMatrix(*this); }
};
