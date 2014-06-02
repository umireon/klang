#pragma once

#include <iostream>

class SyntaxErrorHandler {
public:
	std::string *line;
	int lineno;

	pstr_t invalid_char(pstr_t str);
};
