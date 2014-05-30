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

    double newValue = sin(num->to_f());

    delete num;

    return new KFloat(newValue);
}

KObject* FuncCos::invoke(std::vector<KObject*> args) {
    KNumber *num = dynamic_cast<KNumber*>(args.at(0));
    
    if (args.size() != 1) {
        throw std::invalid_argument("Arity: 1");
    }
    
    if (!num) {
        throw std::invalid_argument("Argument1 is not a KNumber.");
    }

    double newValue = cos(num->to_f());

    delete num;

    return new KFloat(newValue);
}

KObject* FuncTan::invoke(std::vector<KObject*> args) {
    KNumber *num = dynamic_cast<KNumber*>(args.at(0));
    
    if (args.size() != 1) {
        throw std::invalid_argument("Arity: 1");
    }
    
    if (!num) {
        throw std::invalid_argument("Argument1 is not a KNumber.");
    }

    double newValue = tan(num->to_f());

    delete num;

    return new KFloat(newValue);
}


KObject* FuncSinh::invoke(std::vector<KObject*> args) {
    KNumber *num = dynamic_cast<KNumber*>(args.at(0));
    
    if (args.size() != 1) {
        throw std::invalid_argument("Arity: 1");
    }
    
    if (!num) {
        throw std::invalid_argument("Argument1 is not a KNumber.");
    }

    double newValue = sinh(num->to_f());

    delete num;

    return new KFloat(newValue);
}

KObject* FuncCosh::invoke(std::vector<KObject*> args) {
    KNumber *num = dynamic_cast<KNumber*>(args.at(0));
    
    if (args.size() != 1) {
        throw std::invalid_argument("Arity: 1");
    }
    
    if (!num) {
        throw std::invalid_argument("Argument1 is not a KNumber.");
    }

    double newValue = cosh(num->to_f());

    delete num;

    return new KFloat(newValue);
}

KObject* FuncTanh::invoke(std::vector<KObject*> args) {
    KNumber *num = dynamic_cast<KNumber*>(args.at(0));
    
    if (args.size() != 1) {
        throw std::invalid_argument("Arity: 1");
    }
    
    if (!num) {
        throw std::invalid_argument("Argument1 is not a KNumber.");
    }

    double newValue = tanh(num->to_f());

    delete num;

    return new KFloat(newValue);
}

KObject* FuncArcsin::invoke(std::vector<KObject*> args) {
    KNumber *num = dynamic_cast<KNumber*>(args.at(0));
    
    if (args.size() != 1) {
        throw std::invalid_argument("Arity: 1");
    }
    
    if (!num) {
        throw std::invalid_argument("Argument1 is not a KNumber.");
    }

    double newValue = asin(num->to_f());

    delete num;

    return new KFloat(newValue);
}

KObject* FuncArccos::invoke(std::vector<KObject*> args) {
    KNumber *num = dynamic_cast<KNumber*>(args.at(0));
    
    if (args.size() != 1) {
        throw std::invalid_argument("Arity: 1");
    }
    
    if (!num) {
        throw std::invalid_argument("Argument1 is not a KNumber.");
    }

    double newValue = acos(num->to_f());

    delete num;

    return new KFloat(newValue);
}

KObject* FuncArctan::invoke(std::vector<KObject*> args) {
    KNumber *num = dynamic_cast<KNumber*>(args.at(0));
    
    if (args.size() != 1) {
        throw std::invalid_argument("Arity: 1");
    }
    
    if (!num) {
        throw std::invalid_argument("Argument1 is not a KNumber.");
    }

    double newValue = atan(num->to_f());

    delete num;

    return new KFloat(newValue);
}
