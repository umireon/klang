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
};

class FuncHmpr : public FuncFact {
public:
	virtual KObject *invoke(std::vector<KObject*> args);
};
