#include "kobject.h"

#include "ast/AstInvocation.h"

AstInvocation::~AstInvocation()
{
    delete ident;
    delete astArgs;
}

KObject* AstInvocation::evaluate(Binding* b)
{
    std::string name = ident->get_string();
    std::vector<KObject*> args;
    std::vector<AstNode*> &astChildren = astArgs->children;
    std::vector<AstNode*>::iterator iter = astChildren.begin();
    while (iter != astChildren.end()) {
        args.push_back((*iter)->evaluate(b));
        iter++;
    }
    
    KFunction *func = b->get_function(name);
    return func->invoke(args);
}
