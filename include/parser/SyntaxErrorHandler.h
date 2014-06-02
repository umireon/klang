#include <iostream>

class SyntaxErrorHandler {
public:
	pstr_t invalid_char(pstr_t str)
	{
        std::cout << "Unexpected Charactor:" << str[0] << std::endl;
	}

private:
	std::string *line;
	int lineno;
};
