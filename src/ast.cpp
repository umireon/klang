#include <stdlib.h>
#include <sstream>
#include <math.h>

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

long AstAddition::get_long(Binding* b)
{
    std::vector<AstNode*>::iterator iter = children.begin();
    long value = (*iter)->get_long(b);
    iter++;

    while (iter != children.end()) {
        value += (*iter)->get_long(b);
        iter++;
    }

    return value;
}

double AstAddition::get_double(Binding* b)
{
    std::vector<AstNode*>::iterator iter = children.begin();
    double value = (*iter)->get_double(b);
    iter++;
    
    while (iter != children.end()) {
        value += (*iter)->get_double(b);
        iter++;
    }
    
    return value;
}

long AstSubtraction::get_long(Binding* b)
{
    std::vector<AstNode*>::iterator iter = children.begin();
    long value = (*iter)->get_long(b);
    iter++;
    
    while (iter != children.end()) {
        value -= (*iter)->get_long(b);
        iter++;
    }
    
    return value;
}

double AstSubtraction::get_double(Binding* b)
{
    std::vector<AstNode*>::iterator iter = children.begin();
    double value = (*iter)->get_double(b);
    iter++;
    
    while (iter != children.end()) {
        value -= (*iter)->get_double(b);
        iter++;
    }
    
    return value;
}

long AstMultiplication::get_long(Binding* b)
{
    std::vector<AstNode*>::iterator iter = children.begin();
    long value = (*iter)->get_long(b);
    iter++;
    
    while (iter != children.end()) {
        value *= (*iter)->get_long(b);
        iter++;
    }
    
    return value;
}

double AstMultiplication::get_double(Binding* b)
{
    std::vector<AstNode*>::iterator iter = children.begin();
    double value = (*iter)->get_double(b);
    iter++;
    
    while (iter != children.end()) {
        value *= (*iter)->get_double(b);
        iter++;
    }
    
    return value;
}

long AstDivision::get_long(Binding* b)
{
    std::vector<AstNode*>::iterator iter = children.begin();
    long value = (*iter)->get_long(b);
    iter++;
    
    while (iter != children.end()) {
        value /= (*iter)->get_long(b);
        iter++;
    }
    
    return value;
}

double AstDivision::get_double(Binding* b)
{
    std::vector<AstNode*>::iterator iter = children.begin();
    double value = (*iter)->get_double(b);
    iter++;
    
    while (iter != children.end()) {
        value /= (*iter)->get_double(b);
        iter++;
    }
    
    return value;
}

long AstReminder::get_long(Binding* b)
{
    std::vector<AstNode*>::iterator iter = children.begin();
    long value = (*iter)->get_long(b);
    iter++;
    
    while (iter != children.end()) {
        value %= (*iter)->get_long(b);
        iter++;
    }
    
    return value;
}

double AstReminder::get_double(Binding* b)
{
    return get_long(b);
}

long AstPower::get_long(Binding* b)
{
    long value = 1;
    long base = children.at(0)->get_long(b);
    long num = children.at(1)->get_long(b);
    
    if (num < 0) {
        return 0;
    }
    
    for (int i = 0; i < num; i++) {
        value *= base;
    }
    
    return value;
}

double AstPower::get_double(Binding* b)
{
    double base = children.at(0)->get_double(b);
    double e = children.at(1)->get_double(b);

    return pow(base, e);
}

long AstParen::get_long(Binding* b)
{
	return children.at(0)->get_long(b);
}

double AstParen::get_double(Binding* b)
{
	return children.at(0)->get_double(b);
}

long AstInteger::get_long(Binding* b)
{
	return strtol(get_string().c_str(), NULL, 0);
}

double AstInteger::get_double(Binding* b)
{
	return get_long(b);
}

long AstFloat::get_long(Binding* b)
{
	return get_double(b);
}

double AstFloat::get_double(Binding* b)
{
	return strtod(get_string().c_str(), NULL);
}

long AstIdentifier::get_long(Binding* b)
{
    return b->variableTable[get_string()];
}

double AstIdentifier::get_double(Binding* b)
{
    return b->variableTable[get_string()];
}

long AstAssignment::get_long(Binding* b)
{
    long value = children.at(1)->get_long(b);
    b->variableTable[children.at(0)->get_string()] = value;
    return value;
}

double AstAssignment::get_double(Binding* b)
{
    double value = children.at(1)->get_double(b);
    b->variableTable[children.at(0)->get_string()] = value;
    return value;
}

long AstInvocation::get_long(Binding* b)
{
    return get_double(b);
}

double AstInvocation::get_double(Binding* b)
{
    AstIdentifier *ident = static_cast<AstIdentifier*>(children.at(0));
    AstArgument *args = static_cast<AstArgument*>(children.at(1));
    double arg1 = args->children.at(0)->get_double(b);
    std::string name = ident->get_string();

    if (name == std::string("tan")) {
        return tan(arg1);
    } else if (name == std::string("log")) {
        return log(arg1);
    } else if (name == std::string("exit")) {
        exit(0);
    } else {
        return 0;
    }
}

