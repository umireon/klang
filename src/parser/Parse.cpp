#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <sstream>

#include "ast/AstNode.h"

#include "parser/Parse.h"
#include "parser/ParseExpression.h"
#include "parser/ParseAssignment.h"
#include "parser/ParseCompare.h"
#include "parser/ParseArithExpression.h"
#include "parser/ParseTerm.h"
#include "parser/ParsePrimary.h"
#include "parser/ParseFunction.h"
#include "parser/ParseCompound.h"
#include "parser/ParseIf.h"
#include "parser/ParseParen.h"

AstNode* Parse::parse(pstr_t str)
{
    ParseExpression parseExpression;
    ParseAssignment parseAssignment;
    ParseCompare parseCompare;
    ParseArithExpression parseArithExpression;
    ParseTerm parseTerm;
    ParsePrimary parsePrimary;
    ParseFunction parseFunction;
    ParseCompound parseCompound;
    ParseIf parseIf;
    ParseParen parseParen;

    parseExpression.parseNext = &parseAssignment;
    parseAssignment.parseNext = &parseCompare;
    parseCompare.parseNext = &parseArithExpression;
    parseArithExpression.parseNext = &parseTerm;
    parseTerm.parseNext = &parsePrimary;

    parsePrimary.parseExpression = &parseExpression;
    parsePrimary.parseFunction = &parseFunction;
    parsePrimary.parseIf = &parseIf;
    parsePrimary.parseParen = &parseParen;

    parseFunction.parseExpression = &parseExpression;
    parseFunction.parseCompound = &parseCompound;

    parseCompound.parseExpression = &parseExpression;

    parseIf.parseExpression = &parseExpression;
    parseIf.parseCompound = &parseCompound;

    parseParen.parseExpression = &parseExpression;

    return parseExpression.parse(scan(str));
}
