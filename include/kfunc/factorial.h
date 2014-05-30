#include "kobject.h"

class FuncFact : public KFunction {
public:
	virtual KObject *invoke(std::vector<KObject*> args);
protected:
	long factorial(long n);
};

class FuncPerm : public FuncFact {
public:
	virtual KObject *invoke(std::vector<KObject*> args);
};

class FuncComb : public FuncFact {
public:
	virtual KObject *invoke(std::vector<KObject*> args);
	long combination(long n, long r);
};

class FuncHmpr : public FuncComb {
public:
	virtual KObject *invoke(std::vector<KObject*> args);
};
