#include <iostream>

class SyntaxErrorHandler {
public:
	pstr_t invalid_char(pstr_t str)
	{
		return str+1;
	}

private:
	std::string *line;
	int lineno;
};
