#include <vector>

#include "kobject.h"

#include "ast/AstNode.h"
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
