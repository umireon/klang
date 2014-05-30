#include "kobject.h"

class FuncSin : public KFunction {
    KObject* invoke(std::vector<KObject*> args);
};

class FuncCos : public KFunction {
    KObject* invoke(std::vector<KObject*> args);
};

class FuncTan : public KFunction {
    KObject* invoke(std::vector<KObject*> args);
};

class FuncSinh : public KFunction {
    KObject* invoke(std::vector<KObject*> args);
};

class FuncCosh : public KFunction {
    KObject* invoke(std::vector<KObject*> args);
};

class FuncTanh : public KFunction {
    KObject* invoke(std::vector<KObject*> args);
};

class FuncArcsin : public KFunction {
    KObject* invoke(std::vector<KObject*> args);
};

class FuncArccos : public KFunction {
    KObject* invoke(std::vector<KObject*> args);
};

class FuncArctan : public KFunction {
    KObject* invoke(std::vector<KObject*> args);
};
