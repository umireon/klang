#include "kobject.h"

#include "kfunc/FuncFor.h"

KObject* FuncFor::invoke(std::vector<KObject*> args)
{
    if (args.size() != 2) {
		throw std::invalid_argument("for() takes 2 arguments");
    }

    KVector *kvect = dynamic_cast<KVector *>(args[0]);
    KFunction *kfunc = dynamic_cast<KFunction *>(args[1]);

    if (!kvect) {
		throw std::invalid_argument("for(): arg 1 must be vector");
    }
    
    if (!kfunc) {
		throw std::invalid_argument("for(): arg 2 must be function");
    }

    return invoke(kvect, kfunc);
}

KObject* FuncFor::invoke(KVector *kvect, KFunction *kfunc)
{
	dvector &vect = kvect->vect;
	dvector::iterator iter = vect.begin();
	KObject *res = NULL;

	std::vector<KObject *> args(1);
	while (iter != vect.end()) {
		delete res;
		args[0] = new KFloat(*iter);
		res = kfunc->invoke(args);
		iter++;
	}

	return res;
}
