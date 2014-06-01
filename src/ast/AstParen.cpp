#include "kobject.h"

#include "ast/AstParen.h"

KObject* AstParen::evaluate(Binding* b)
{
    return children.at(0)->evaluate(b);
}