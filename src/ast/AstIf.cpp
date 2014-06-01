#include <vector>

#include "kobject/KObject.h"
#include "kobject/KNil.h"
#include "kobject/KInteger.h"
#include "Binding.h"

#include "ast/AstIf.h"

AstIf::~AstIf()
{
    std::vector<AstNode *>::iterator iter;
    iter = cond.begin();
    while (iter != cond.end()) {
        delete *iter;
        iter++;
    }

    iter = body.begin();
    while (iter != body.end()) {
        delete *iter;
        iter++;
    }
}

KObject *AstIf::evaluate(Binding *b)
{
    for (int i = 0; i < cond.size(); i++) {
        KObject *res = cond[i]->evaluate(b);
        int value = 1;

        if (res->get_type() == KObject::INTEGER) {
            KInteger *kint = dynamic_cast<KInteger *>(res);
            value = kint->to_i();
        }

        delete res;

        if (value) {
            return body[i]->evaluate(b);
        }
    }

    if (cond.size() < body.size()) {
        return body[cond.size()]->evaluate(b);
    } else {
        return new KNil();
    }
}
