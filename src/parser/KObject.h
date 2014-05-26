#include <map>

#include <boost/numeric/ublas/vector.hpp>

using namespace boost::numeric;

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

class Binding : public KObject
{
public:
	std::map<std::string, long> variableTable;
	std::map<std::string, KObject*> locals;
    
	KObject* get_local(std::string name);
	void set_local(std::string name, KObject* value);
    
	KFunction* get_function(std::string name);
};
