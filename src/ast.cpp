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

long AstAddition::get_long()
{
    std::vector<AstNode*>::iterator iter = children.begin();
    long value = (*iter)->get_long();
    iter++;

    while (iter != children.end()) {
        value += (*iter)->get_long();
        iter++;
    }

    return value;
}

double AstAddition::get_double()
{
    std::vector<AstNode*>::iterator iter = children.begin();
    double value = (*iter)->get_double();
    iter++;
    
    while (iter != children.end()) {
        value += (*iter)->get_double();
        iter++;
    }
    
    return value;
}

long AstSubtraction::get_long()
{
    std::vector<AstNode*>::iterator iter = children.begin();
    long value = (*iter)->get_long();
    iter++;
    
    while (iter != children.end()) {
        value -= (*iter)->get_long();
        iter++;
    }
    
    return value;
}

double AstSubtraction::get_double()
{
    std::vector<AstNode*>::iterator iter = children.begin();
    double value = (*iter)->get_double();
    iter++;
    
    while (iter != children.end()) {
        value -= (*iter)->get_double();
        iter++;
    }
    
    return value;
}

long AstMultiplication::get_long()
{
    std::vector<AstNode*>::iterator iter = children.begin();
    long value = (*iter)->get_long();
    iter++;
    
    while (iter != children.end()) {
        value *= (*iter)->get_long();
        iter++;
    }
    
    return value;
}

double AstMultiplication::get_double()
{
    std::vector<AstNode*>::iterator iter = children.begin();
    double value = (*iter)->get_double();
    iter++;
    
    while (iter != children.end()) {
        value *= (*iter)->get_double();
        iter++;
    }
    
    return value;
}

long AstDivision::get_long()
{
    std::vector<AstNode*>::iterator iter = children.begin();
    long value = (*iter)->get_long();
    iter++;
    
    while (iter != children.end()) {
        value /= (*iter)->get_long();
        iter++;
    }
    
    return value;
}

double AstDivision::get_double()
{
    std::vector<AstNode*>::iterator iter = children.begin();
    double value = (*iter)->get_double();
    iter++;
    
    while (iter != children.end()) {
        value /= (*iter)->get_double();
        iter++;
    }
    
    return value;
}

long AstReminder::get_long()
{
    std::vector<AstNode*>::iterator iter = children.begin();
    long value = (*iter)->get_long();
    iter++;
    
    while (iter != children.end()) {
        value %= (*iter)->get_long();
        iter++;
    }
    
    return value;
}

double AstReminder::get_double()
{
    return get_long();
}

long AstPower::get_long()
{
    long value = 1;
    long base = children.at(0)->get_long();
    long num = children.at(1)->get_long();
    
    if (num < 0) {
        return 0;
    }
    
    for (int i = 0; i < num; i++) {
        value *= base;
    }
    
    return value;
}

double AstPower::get_double()
{
    double base = children.at(0)->get_double();
    double e = children.at(1)->get_double();

    return pow(base, e);
}

long AstParen::get_long()
{
	return children.at(0)->get_long();
}

double AstParen::get_double()
{
	return children.at(0)->get_double();
}

long AstInteger::get_long()
{
	return strtol(get_string().c_str(), NULL, 0);
}

double AstInteger::get_double()
{
	return get_long();
}

long AstFloat::get_long()
{
	return get_double();
}

double AstFloat::get_double()
{
	return strtod(get_string().c_str(), NULL);
}
