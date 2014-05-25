#include <stdlib.h>
#include <sstream>
#include <math.h>

#include "ast.h"

Object* Binding::get_local(std::string name)
{
    return locals[name];
}

void Binding::set_local(std::string name, Object* value)
{
    locals[name] = value;
}

Function* Binding::get_function(std::string name)
{
    Object* func = get_local(name);
    return static_cast<Function*>(func);
}

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

Number* AstAddition::evaluate(Binding* b)
{
    long valuei = 0;
    double valuef = 0;
    bool isfloat = false;
    std::vector<AstNode*>::iterator iter = children.begin();

    while (iter != children.end()) {
        Object *obj = (*iter)->evaluate(b);
        Number *num = static_cast<Number*>(obj);
        valuei += num->to_i();
        valuef += num->to_f();
        isfloat = isfloat || (num->type == Number::FLOAT);
        iter++;
    }

    if (isfloat) {
        return new Float(valuef);
    } else {
        return new Integer(valuei);
    }
}

Number* AstSubtraction::evaluate(Binding* b)
{
    std::vector<AstNode*>::iterator iter = children.begin();
    Object *obj = (*iter)->evaluate(b);
    Number *num = static_cast<Number*>(obj);
    iter++;

    long valuei = num->to_i();
    double valuef = num->to_f();
    bool isfloat = num->type == Number::FLOAT;

    while (iter != children.end()) {
        obj = (*iter)->evaluate(b);
        num = static_cast<Number*>(obj);
        valuei -= num->to_i();
        valuef -= num->to_f();
        isfloat = isfloat || (num->type == Number::FLOAT);
        iter++;
    }

    if (isfloat) {
        return new Float(valuef);
    } else {
        return new Integer(valuei);
    }
}

Number* AstMultiplication::evaluate(Binding* b)
{
    std::vector<AstNode*>::iterator iter = children.begin();
    Object *obj = (*iter)->evaluate(b);
    Number *num = static_cast<Number*>(obj);
    iter++;

    long valuei = num->to_i();
    double valuef = num->to_f();
    bool isfloat = num->type == Number::FLOAT;

    while (iter != children.end()) {
        obj = (*iter)->evaluate(b);
        num = static_cast<Number*>(obj);
        valuei *= num->to_i();
        valuef *= num->to_f();
        isfloat = isfloat || (num->type == Number::FLOAT);
        iter++;
    }

    if (isfloat) {
        return new Float(valuef);
    } else {
        return new Integer(valuei);
    }
}

Number* AstDivision::evaluate(Binding* b)
{
    std::vector<AstNode*>::iterator iter = children.begin();
    Object *obj = (*iter)->evaluate(b);
    Number *num = static_cast<Number*>(obj);
    iter++;

    long valuei = num->to_i();
    double valuef = num->to_f();
    bool isfloat = num->type == Number::FLOAT;

    while (iter != children.end()) {
        obj = (*iter)->evaluate(b);
        num = static_cast<Number*>(obj);
        if (!isfloat) {
            valuei /= num->to_i();
        }
        valuef /= num->to_f();
        isfloat = isfloat || (num->type == Number::FLOAT);
        iter++;
    }

    if (isfloat) {
        return new Float(valuef);
    } else {
        return new Integer(valuei);
    }
}

Integer* AstReminder::evaluate(Binding* b)
{
    std::vector<AstNode*>::iterator iter = children.begin();
    Object *obj = (*iter)->evaluate(b);
    Number *num = static_cast<Number*>(obj);
    iter++;

    long value = num->to_i();

    while (iter != children.end()) {
        obj = (*iter)->evaluate(b);
        num = static_cast<Number*>(obj);
        value %= num->to_i();
        iter++;
    }

    return new Integer(value);
}

Number* AstPower::evaluate(Binding* b)
{
    Number *baseNum = static_cast<Number*>(children.at(0)->evaluate(b));
    Number *eNum = static_cast<Number*>(children.at(1)->evaluate(b));

    if (baseNum->type == Number::FLOAT || eNum->type == Number::FLOAT) {
        return new Float(pow(baseNum->to_f(), eNum->to_i()));
    } else {
        long base = baseNum->to_i();
        long num = eNum->to_i();
        long value = 1;
        for (int i = 0; i < num; i++) {
            value *= base;
        }
        return new Integer(value);
    }
}

Object* AstParen::evaluate(Binding* b)
{
    return children.at(0)->evaluate(b);
}

Integer* AstInteger::evaluate(Binding* b)
{
    return new Integer(strtol(get_string().c_str(), NULL, 0));
}

Float* AstFloat::evaluate(Binding* b)
{
    return new Float(strtod(get_string().c_str(), NULL));
}

Object* AstIdentifier::evaluate(Binding* b)
{
    std::string name = get_string();
    return b->get_local(name);
}

Object* AstAssignment::evaluate(Binding* b)
{
    std::string name = children.at(0)->get_string();
    Object *value = children.at(1)->evaluate(b);
    b->set_local(name, value);
    return value;
}

Object* AstInvocation::evaluate(Binding* b)
{
    AstIdentifier *ident = static_cast<AstIdentifier*>(children.at(0));
    AstArgument *astArgs = static_cast<AstArgument*>(children.at(1));

    std::string name = ident->get_string();

    std::vector<Object*> args;
    std::vector<AstNode*> &astChildren = astArgs->children;
    std::vector<AstNode*>::iterator iter = astChildren.begin();
    while (iter != astChildren.end()) {
        args.push_back((*iter)->evaluate(b));
        iter++;
    }

    Function *func = b->get_function(name);
    return func->invoke(args);
}
