#include <algorithm>
#include <iostream>

#include "parser/types.h"
#include "parser/SyntaxErrorHandler.h"

pstr_t SyntaxErrorHandler::invalid_char(pstr_t str, const char *func)
{
    if (str == line->end()) {
        output << "Unexpected End Of Line in line " << lineno - 1 << std::endl;
        output << *line << std::endl;
        output << "Raised in " << func << std::endl;
    } else {
        int reallineno = lineno - std::count(str, line->end(), '\n');
        std::string before(line->begin(), str);
        std::string after(str + 1, line->end());
        output << "Unexpected Character: " << *str << "in line " << reallineno << std::endl;
        output << "Raised in " << func << std::endl;
        output << before << "_" << *str << "_" << after << std::endl;
        str++;
    }
    
    return str;
}

pstr_t SyntaxErrorHandler::never_reach(pstr_t str, const char *func)
{
    output << "[BUG] Never Reach in " << func << std::endl;
	return str;
}
