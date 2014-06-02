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
    ParseParameter parseParameter;
    ParseIf parseIf;
    ParseParen parseParen;
    TokenNumber tokenNumber;
    TokenIdentifier tokenIdentifier;

    parseExpression.parseNext = &parseAssignment;
    parseAssignment.parseNext = &parseCompare;
    parseCompare.parseNext = &parseArithExpression;
    parseArithExpression.parseNext = &parseTerm;
    parseTerm.parseNext = &parsePrimary;

    parsePrimary.parseExpression = &parseExpression;
    parsePrimary.parseFunction = &parseFunction;
    parsePrimary.parseIf = &parseIf;
    parsePrimary.parseParen = &parseParen;
    parsePrimary.tokenNumber = &tokenNumber;
    parsePrimary.tokenIdentifier = &tokenIdentifier;

    parseFunction.parseExpression = &parseExpression;
    parseFunction.parseCompound = &parseCompound;
    parseFunction.parseParameter = &parseParameter;

    parseCompound.parseExpression = &parseExpression;

    parseParameter.tokenIdentifier = &tokenIdentifier;

    parseIf.parseExpression = &parseExpression;
    parseIf.parseCompound = &parseCompound;
    parseIf.tokenIdentifier = &tokenIdentifier;

    parseParen.parseExpression = &parseExpression;
    
    parseExpression.syntaxErrorHandler = syntaxErrorHandler;
    parseAssignment.syntaxErrorHandler = syntaxErrorHandler;
    parseCompare.syntaxErrorHandler = syntaxErrorHandler;
    parseArithExpression.syntaxErrorHandler = syntaxErrorHandler;
    parseTerm.syntaxErrorHandler = syntaxErrorHandler;
    parsePrimary.syntaxErrorHandler = syntaxErrorHandler;
    parseFunction.syntaxErrorHandler = syntaxErrorHandler;
    parseCompound.syntaxErrorHandler = syntaxErrorHandler;
    parseParameter.syntaxErrorHandler = syntaxErrorHandler;
    parseIf.syntaxErrorHandler = syntaxErrorHandler;
    parseParen.syntaxErrorHandler = syntaxErrorHandler;
    tokenNumber.syntaxErrorHandler = syntaxErrorHandler;
    tokenIdentifier.syntaxErrorHandler = syntaxErrorHandler;

    return parseExpression.parse(scan(str));
}
