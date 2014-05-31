#include "kobject.h"

class FuncSin : public KFunction {
    KObject* invoke(std::vector<KObject*> args);
	virtual FuncSin *clone() const { return new FuncSin(*this); }
};

class FuncCos : public KFunction {
    KObject* invoke(std::vector<KObject*> args);
	virtual FuncCos *clone() const { return new FuncCos(*this); }
};

class FuncTan : public KFunction {
    KObject* invoke(std::vector<KObject*> args);
	virtual FuncTan *clone() const { return new FuncTan(*this); }
};

class FuncSinh : public KFunction {
    KObject* invoke(std::vector<KObject*> args);
	virtual FuncSinh *clone() const { return new FuncSinh(*this); }
};

class FuncCosh : public KFunction {
    KObject* invoke(std::vector<KObject*> args);
	virtual FuncCosh *clone() const { return new FuncCosh(*this); }
};

class FuncTanh : public KFunction {
    KObject* invoke(std::vector<KObject*> args);
	virtual FuncTanh *clone() const { return new FuncTanh(*this); }
};

class FuncArcsin : public KFunction {
    KObject* invoke(std::vector<KObject*> args);
	virtual FuncArcsin *clone() const { return new FuncArcsin(*this); }
};

class FuncArccos : public KFunction {
    KObject* invoke(std::vector<KObject*> args);
	virtual FuncArccos *clone() const { return new FuncArccos(*this); }
};

class FuncArctan : public KFunction {
    KObject* invoke(std::vector<KObject*> args);
	virtual FuncArctan *clone() const { return new FuncArctan(*this); }
};
