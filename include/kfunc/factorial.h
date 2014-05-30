#include "kobject.h"

class FuncFact : public KFunction {
public:
	virtual KObject *invoke(std::vector<KObject*> args);
	virtual FuncFact *clone() const { return new FuncFact(*this); }
protected:
	long factorial(long n);
};

class FuncPerm : public FuncFact {
public:
	virtual KObject *invoke(std::vector<KObject*> args);
	virtual FuncFact *clone() const { return new FuncPerm(*this); }
};

class FuncComb : public FuncFact {
public:
	virtual KObject *invoke(std::vector<KObject*> args);
	virtual FuncFact *clone() const { return new FuncComb(*this); }
	long combination(long n, long r);
};

class FuncHmpr : public FuncComb {
public:
	virtual KObject *invoke(std::vector<KObject*> args);
	virtual FuncFact *clone() const { return new FuncHmpr(*this); }
};
