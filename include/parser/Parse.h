#pragma once

#include "ast/AstNode.h"

#include "parser/types.h"
#include "parser/BaseParse.h"

class Parse : public BaseParse
{
public:
	AstNode *parse(pstr_t str);
};
