#pragma once

#include <string>

#include "ast/AstNode.h"

#include "parser/types.h"
#include "parser/SyntaxErrorHandler.h"

class BaseParse
{
public:
	SyntaxErrorHandler *syntaxErrorHandler;
    std::string *line;

    virtual ~BaseParse() {}
	virtual AstNode *parse(pstr_t str) = 0;

protected:
	virtual bool is_whitespace(pstr_t str);
	virtual pstr_t scan(pstr_t str);
};
