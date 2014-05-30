#include "kobject.h"

#include "kfunc/triangle.h"

KObject* FuncSin::invoke(std::vector<KObject*> args) {
    KNumber *num = dynamic_cast<KNumber*>(args.at(0));
    
    if (args.size() != 1) {
        throw std::invalid_argument("Arity: 1");
    }
    
    if (!num) {
        throw std::invalid_argument("Argument1 is not a KNumber.");
    }

    return new KFloat(sin(num->to_f()));
}

KObject* FuncCos::invoke(std::vector<KObject*> args) {
    KNumber *num = dynamic_cast<KNumber*>(args.at(0));
    
    if (args.size() != 1) {
        throw std::invalid_argument("Arity: 1");
    }
    
    if (!num) {
        throw std::invalid_argument("Argument1 is not a KNumber.");
    }

    return new KFloat(cos(num->to_f()));
}

KObject* FuncTan::invoke(std::vector<KObject*> args) {
    KNumber *num = dynamic_cast<KNumber*>(args.at(0));
    
    if (args.size() != 1) {
        throw std::invalid_argument("Arity: 1");
    }
    
    if (!num) {
        throw std::invalid_argument("Argument1 is not a KNumber.");
    }

    return new KFloat(tan(num->to_f()));
}


KObject* FuncSinh::invoke(std::vector<KObject*> args) {
    KNumber *num = dynamic_cast<KNumber*>(args.at(0));
    
    if (args.size() != 1) {
        throw std::invalid_argument("Arity: 1");
    }
    
    if (!num) {
        throw std::invalid_argument("Argument1 is not a KNumber.");
    }

    return new KFloat(sinh(num->to_f()));
}

KObject* FuncCosh::invoke(std::vector<KObject*> args) {
    KNumber *num = dynamic_cast<KNumber*>(args.at(0));
    
    if (args.size() != 1) {
        throw std::invalid_argument("Arity: 1");
    }
    
    if (!num) {
        throw std::invalid_argument("Argument1 is not a KNumber.");
    }

    return new KFloat(cosh(num->to_f()));
}

KObject* FuncTanh::invoke(std::vector<KObject*> args) {
    KNumber *num = dynamic_cast<KNumber*>(args.at(0));
    
    if (args.size() != 1) {
        throw std::invalid_argument("Arity: 1");
    }
    
    if (!num) {
        throw std::invalid_argument("Argument1 is not a KNumber.");
    }

    return new KFloat(tanh(num->to_f()));
}

KObject* FuncArcsin::invoke(std::vector<KObject*> args) {
    KNumber *num = dynamic_cast<KNumber*>(args.at(0));
    
    if (args.size() != 1) {
        throw std::invalid_argument("Arity: 1");
    }
    
    if (!num) {
        throw std::invalid_argument("Argument1 is not a KNumber.");
    }

    return new KFloat(asin(num->to_f()));
}

KObject* FuncArccos::invoke(std::vector<KObject*> args) {
    KNumber *num = dynamic_cast<KNumber*>(args.at(0));
    
    if (args.size() != 1) {
        throw std::invalid_argument("Arity: 1");
    }
    
    if (!num) {
        throw std::invalid_argument("Argument1 is not a KNumber.");
    }

    return new KFloat(acos(num->to_f()));
}

KObject* FuncArctan::invoke(std::vector<KObject*> args) {
    KNumber *num = dynamic_cast<KNumber*>(args.at(0));
    
    if (args.size() != 1) {
        throw std::invalid_argument("Arity: 1");
    }
    
    if (!num) {
        throw std::invalid_argument("Argument1 is not a KNumber.");
    }

    return new KFloat(atan(num->to_f()));
}
