#include "parser/types.h"
#include "parser/BaseParse.h"

bool BaseParse::is_whitespace(pstr_t str) {
	return *str == ' ';
}

pstr_t BaseParse::scan(pstr_t str) {
	while (is_whitespace(str)) {
        std::cout << *str;
		str++;
	}

    return str;
}
