#pragma once

#include <stdexcept>
#include <string>

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
