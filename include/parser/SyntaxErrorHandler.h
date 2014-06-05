#pragma once

#include <iostream>

class SyntaxErrorHandler {
public:
	std::ostream &output;
	std::string *line;
	int lineno;

	SyntaxErrorHandler() : output(std::cout) {}
	SyntaxErrorHandler(std::ostream &os) : output(os) {}

	pstr_t invalid_char(pstr_t str, const char *func);
	pstr_t never_reach(pstr_t str, const char *func);
};
