#include <stdlib.h>
#include <math.h>

#include <sstream>

#include "ast.h"

std::string AstNode::get_string() {
    return std::string(strhead, strtail - strhead);
}

AstParentNode::~AstParentNode(void)
{
	int size = children.size();
	for (int i = 0; i < size; i++) {
		delete children.at(i);
	}
}

KNumber* AstAddition::evaluate(Binding* b)
{
    long valuei = 0;
    double valuef = 0;
    bool isfloat = false;
    std::vector<AstNode*>::iterator iter = children.begin();
    
    while (iter != children.end()) {
        KObject *obj = (*iter)->evaluate(b);
        KNumber *num = static_cast<KNumber*>(obj);
        valuei += num->to_i();
        valuef += num->to_f();
        isfloat = isfloat || (num->type == KNumber::FLOAT);
        iter++;
    }
    
    if (isfloat) {
        return new KFloat(valuef);
    } else {
        return new KInteger(valuei);
    }
}

KNumber* AstSubtraction::evaluate(Binding* b)
{
    std::vector<AstNode*>::iterator iter = children.begin();
    KObject *obj = (*iter)->evaluate(b);
    KNumber *num = static_cast<KNumber*>(obj);
    iter++;
    
    long valuei = num->to_i();
    double valuef = num->to_f();
    bool isfloat = num->type == KNumber::FLOAT;
    
    while (iter != children.end()) {
        obj = (*iter)->evaluate(b);
        num = static_cast<KNumber*>(obj);
        valuei -= num->to_i();
        valuef -= num->to_f();
        isfloat = isfloat || (num->type == KNumber::FLOAT);
        iter++;
    }
    
    if (isfloat) {
        return new KFloat(valuef);
    } else {
        return new KInteger(valuei);
    }
}

KNumber* AstMultiplication::evaluate(Binding* b)
{
    std::vector<AstNode*>::iterator iter = children.begin();
    KObject *obj = (*iter)->evaluate(b);
    KNumber *num = static_cast<KNumber*>(obj);
    iter++;
    
    long valuei = num->to_i();
    double valuef = num->to_f();
    bool isfloat = num->type == KNumber::FLOAT;
    
    while (iter != children.end()) {
        obj = (*iter)->evaluate(b);
        num = static_cast<KNumber*>(obj);
        valuei *= num->to_i();
        valuef *= num->to_f();
        isfloat = isfloat || (num->type == KNumber::FLOAT);
        iter++;
    }
    
    if (isfloat) {
        return new KFloat(valuef);
    } else {
        return new KInteger(valuei);
    }
}

KNumber* AstDivision::evaluate(Binding* b)
{
    std::vector<AstNode*>::iterator iter = children.begin();
    KObject *obj = (*iter)->evaluate(b);
    KNumber *num = static_cast<KNumber*>(obj);
    iter++;
    
    long valuei = num->to_i();
    double valuef = num->to_f();
    bool isfloat = num->type == KNumber::FLOAT;
    
    while (iter != children.end()) {
        obj = (*iter)->evaluate(b);
        num = static_cast<KNumber*>(obj);
        if (!isfloat) {
            valuei /= num->to_i();
        }
        valuef /= num->to_f();
        isfloat = isfloat || (num->type == KNumber::FLOAT);
        iter++;
    }
    
    if (isfloat) {
        return new KFloat(valuef);
    } else {
        return new KInteger(valuei);
    }
}

KInteger* AstReminder::evaluate(Binding* b)
{
    std::vector<AstNode*>::iterator iter = children.begin();
    KObject *obj = (*iter)->evaluate(b);
    KNumber *num = static_cast<KNumber*>(obj);
    iter++;
    
    long value = num->to_i();
    
    while (iter != children.end()) {
        obj = (*iter)->evaluate(b);
        num = static_cast<KNumber*>(obj);
        value %= num->to_i();
        iter++;
    }
    
    return new KInteger(value);
}

KNumber* AstPower::evaluate(Binding* b)
{
    KNumber *baseNum = static_cast<KNumber*>(children.at(0)->evaluate(b));
    KNumber *eNum = static_cast<KNumber*>(children.at(1)->evaluate(b));
    
    if (baseNum->type == KNumber::FLOAT || eNum->type == KNumber::FLOAT) {
        return new KFloat(pow(baseNum->to_f(), eNum->to_i()));
    } else {
        long base = baseNum->to_i();
        long num = eNum->to_i();
        long value = 1;
        for (int i = 0; i < num; i++) {
            value *= base;
        }
        return new KInteger(value);
    }
}

KObject* AstParen::evaluate(Binding* b)
{
    return children.at(0)->evaluate(b);
}

KInteger* AstInteger::evaluate(Binding* b)
{
    return new KInteger(strtol(get_string().c_str(), NULL, 0));
}

KFloat* AstFloat::evaluate(Binding* b)
{
    return new KFloat(strtod(get_string().c_str(), NULL));
}

KObject* AstIdentifier::evaluate(Binding* b)
{
    std::string name = get_string();
    return b->get_local(name);
}

KObject* AstAssignment::evaluate(Binding* b)
{
    std::string name = children.at(0)->get_string();
    KObject *value = children.at(1)->evaluate(b);
    b->set_local(name, value);
    return value;
}

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
