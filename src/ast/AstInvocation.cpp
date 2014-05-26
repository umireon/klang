#include "kobject.h"

#include "ast.h"

KObject* AstInvocation::evaluate(Binding* b)
{
    AstIdentifier *ident = static_cast<AstIdentifier*>(children.at(0));
    AstArgument *astArgs = static_cast<AstArgument*>(children.at(1));
    
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