#include <algorithm>

#include "kobject/KObject.h"
#include "kobject/KNumber.h"
#include "kobject/KFloat.h"
#include "kobject/KNil.h"
#include "kobject/KFunction.h"

#include "kfunc/triangle.h"

KObject* FuncSin::invoke(std::vector<KObject*> args) {
    if (args.size() == 1) {
        switch (args[0]->get_type()) {
            case KObject::INTEGER:
            case KObject::FLOAT:
                {
                    KNumber *knum = static_cast<KNumber *>(args[0]);
                    double value = knum->to_f();
                    delete knum;
                    return new KFloat(sin(value));
                }
            case KObject::VECTOR:
                {
                    KVector *kvect = static_cast<KVector *>(args[0]);
                    dvector &vect = kvect->vect;
					std::transform(vect.begin(), vect.end(), vect.begin(), (double(*)(double))std::sin);
                    return kvect;
                }
            default:
                ;
        }
    } else {
        std::cout << "WARNING: seq arity 2" << std::endl;
    }

    std::vector<KObject *>::iterator iter = args.begin();
    while (iter != args.end()) {
        delete *iter;
        iter++;
    }

    return new KNil();
}

KObject* FuncCos::invoke(std::vector<KObject*> args) {
    if (args.size() == 1) {
        switch (args[0]->get_type()) {
            case KObject::INTEGER:
            case KObject::FLOAT:
                {
                    KNumber *knum = static_cast<KNumber *>(args[0]);
                    double value = knum->to_f();
                    delete knum;
                    return new KFloat(cos(value));
                }
            case KObject::VECTOR:
                {
                    KVector *kvect = static_cast<KVector *>(args[0]);
                    dvector &vect = kvect->vect;
					std::transform(vect.begin(), vect.end(), vect.begin(), (double(*)(double))std::cos);
                    return kvect;
                }
            default:
                ;
        }
    } else {
        std::cout << "WARNING: seq arity 2" << std::endl;
    }

    std::vector<KObject *>::iterator iter = args.begin();
    while (iter != args.end()) {
        delete *iter;
        iter++;
    }

    return new KNil();
}

KObject* FuncTan::invoke(std::vector<KObject*> args) {
    if (args.size() == 1) {
        switch (args[0]->get_type()) {
            case KObject::INTEGER:
            case KObject::FLOAT:
                {
                    KNumber *knum = static_cast<KNumber *>(args[0]);
                    double value = knum->to_f();
                    delete knum;
                    return new KFloat(tan(value));
                }
            case KObject::VECTOR:
                {
                    KVector *kvect = static_cast<KVector *>(args[0]);
                    dvector &vect = kvect->vect;
					std::transform(vect.begin(), vect.end(), vect.begin(), (double(*)(double))std::tan);
                    return kvect;
                }
            default:
                ;
        }
    } else {
        std::cout << "WARNING: seq arity 2" << std::endl;
    }

    std::vector<KObject *>::iterator iter = args.begin();
    while (iter != args.end()) {
        delete *iter;
        iter++;
    }

    return new KNil();
}


KObject* FuncSinh::invoke(std::vector<KObject*> args) {
    if (args.size() == 1) {
        switch (args[0]->get_type()) {
            case KObject::INTEGER:
            case KObject::FLOAT:
                {
                    KNumber *knum = static_cast<KNumber *>(args[0]);
                    double value = knum->to_f();
                    delete knum;
                    return new KFloat(sinh(value));
                }
            case KObject::VECTOR:
                {
                    KVector *kvect = static_cast<KVector *>(args[0]);
                    dvector &vect = kvect->vect;
					std::transform(vect.begin(), vect.end(), vect.begin(), (double(*)(double))std::sinh);
                    return kvect;
                }
            default:
                ;
        }
    } else {
        std::cout << "WARNING: seq arity 2" << std::endl;
    }

    std::vector<KObject *>::iterator iter = args.begin();
    while (iter != args.end()) {
        delete *iter;
        iter++;
    }

    return new KNil();
}

KObject* FuncCosh::invoke(std::vector<KObject*> args) {

    if (args.size() == 1) {
        switch (args[0]->get_type()) {
            case KObject::INTEGER:
            case KObject::FLOAT:
                {
                    KNumber *knum = static_cast<KNumber *>(args[0]);
                    double value = knum->to_f();
                    delete knum;
                    return new KFloat(cosh(value));
                }
            case KObject::VECTOR:
                {
                    KVector *kvect = static_cast<KVector *>(args[0]);
                    dvector &vect = kvect->vect;
					std::transform(vect.begin(), vect.end(), vect.begin(), (double(*)(double))std::cosh);
                    return kvect;
                }
            default:
                ;
        }
    } else {
        std::cout << "WARNING: seq arity 2" << std::endl;
    }

    std::vector<KObject *>::iterator iter = args.begin();
    while (iter != args.end()) {
        delete *iter;
        iter++;
    }

    return new KNil();
}

KObject* FuncTanh::invoke(std::vector<KObject*> args) {
    if (args.size() == 1) {
        switch (args[0]->get_type()) {
            case KObject::INTEGER:
            case KObject::FLOAT:
                {
                    KNumber *knum = static_cast<KNumber *>(args[0]);
                    double value = knum->to_f();
                    delete knum;
                    return new KFloat(tanh(value));
                }
            case KObject::VECTOR:
                {
                    KVector *kvect = static_cast<KVector *>(args[0]);
                    dvector &vect = kvect->vect;
					std::transform(vect.begin(), vect.end(), vect.begin(), (double(*)(double))std::tanh);
                    return kvect;
                }
            default:
                ;
        }
    } else {
        std::cout << "WARNING: seq arity 2" << std::endl;
    }

    std::vector<KObject *>::iterator iter = args.begin();
    while (iter != args.end()) {
        delete *iter;
        iter++;
    }

    return new KNil();
}

KObject* FuncArcsin::invoke(std::vector<KObject*> args) {
    if (args.size() == 1) {
        switch (args[0]->get_type()) {
            case KObject::INTEGER:
            case KObject::FLOAT:
                {
                    KNumber *knum = static_cast<KNumber *>(args[0]);
                    double value = knum->to_f();
                    delete knum;
                    return new KFloat(asin(value));
                }
            case KObject::VECTOR:
                {
                    KVector *kvect = static_cast<KVector *>(args[0]);
                    dvector &vect = kvect->vect;
					std::transform(vect.begin(), vect.end(), vect.begin(), (double(*)(double))std::asin);
                    return kvect;
                }
            default:
                ;
        }
    } else {
        std::cout << "WARNING: seq arity 2" << std::endl;
    }

    std::vector<KObject *>::iterator iter = args.begin();
    while (iter != args.end()) {
        delete *iter;
        iter++;
    }

    return new KNil();
}

KObject* FuncArccos::invoke(std::vector<KObject*> args) {
    if (args.size() == 1) {
        switch (args[0]->get_type()) {
            case KObject::INTEGER:
            case KObject::FLOAT:
                {
                    KNumber *knum = static_cast<KNumber *>(args[0]);
                    double value = knum->to_f();
                    delete knum;
                    return new KFloat(acos(value));
                }
            case KObject::VECTOR:
                {
                    KVector *kvect = static_cast<KVector *>(args[0]);
                    dvector &vect = kvect->vect;
					std::transform(vect.begin(), vect.end(), vect.begin(), (double(*)(double))std::acos);
                    return kvect;
                }
            default:
                ;
        }
    } else {
        std::cout << "WARNING: seq arity 2" << std::endl;
    }

    std::vector<KObject *>::iterator iter = args.begin();
    while (iter != args.end()) {
        delete *iter;
        iter++;
    }

    return new KNil();
}

KObject* FuncArctan::invoke(std::vector<KObject*> args) {
    if (args.size() == 1) {
        switch (args[0]->get_type()) {
            case KObject::INTEGER:
            case KObject::FLOAT:
                {
                    KNumber *knum = static_cast<KNumber *>(args[0]);
                    double value = knum->to_f();
                    delete knum;
                    return new KFloat(atan(value));
                }
            case KObject::VECTOR:
                {
                    KVector *kvect = static_cast<KVector *>(args[0]);
                    dvector &vect = kvect->vect;
					std::transform(vect.begin(), vect.end(), vect.begin(), (double(*)(double))std::atan);
                    return kvect;
                }
            default:
                ;
        }
    } else {
        std::cout << "WARNING: seq arity 2" << std::endl;
    }

    std::vector<KObject *>::iterator iter = args.begin();
    while (iter != args.end()) {
        delete *iter;
        iter++;
    }

    return new KNil();
}
