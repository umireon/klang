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
    SyntaxErrorHandler handler;
    SyntaxErrorHandler *seh = &handler;
    
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
    
    parseExpression.syntaxErrorHandler = seh;
    parseAssignment.syntaxErrorHandler = seh;
    parseCompare.syntaxErrorHandler = seh;
    parseArithExpression.syntaxErrorHandler = seh;
    parseTerm.syntaxErrorHandler = seh;
    parsePrimary.syntaxErrorHandler = seh;
    parseFunction.syntaxErrorHandler = seh;
    parseCompound.syntaxErrorHandler = seh;
    parseParameter.syntaxErrorHandler = seh;
    parseIf.syntaxErrorHandler = seh;
    parseParen.syntaxErrorHandler = seh;
    tokenNumber.syntaxErrorHandler = seh;
    tokenIdentifier.syntaxErrorHandler = seh;

    return parseExpression.parse(scan(str));
}
