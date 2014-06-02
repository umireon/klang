#include <algorithm>
#include <iostream>

#include "parser/types.h"
#include "parser/SyntaxErrorHandler.h"

pstr_t SyntaxErrorHandler::invalid_char(pstr_t str)
{
    std::string before(line->begin(), str);
    std::string after(str + 1, line->end());
    
    int reallineno = lineno - std::count(str, line->end(), '\n');
    std::cout << "Unexpected Character: " << *str << "in line " << reallineno << std::endl;
    std::cout << before << "_" << *str << "_" << after << std::endl;
    return str+1;
}