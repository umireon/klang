#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <sstream>
#include "ast.h"
#include "parser.h"

AstNode* Parse::parse(pstr_t str)
{
    str = scan_lexical_symbol(str);
    return this->parse_statement(str);
}

AstNode* Parse::parse_statement(pstr_t str)
{
    enum SymbolType type = get_symbol(str[0]);

    switch (type) {
        case SYMBOL_NUMBER_ZERO:
        case SYMBOL_NUMBER_OCT:
        case SYMBOL_NUMBER_DEC:
        case SYMBOL_SIGN_MINUS:
        case SYMBOL_SIGN_PLUS:
        case SYMBOL_PAREN_LEFT:
        case SYMBOL_ALPHABET_HEXUPPER:
        case SYMBOL_ALPHABET_HEXLOWER:
        case SYMBOL_ALPHABET_X:
        case SYMBOL_ALPHABET:
            ParseExpression p;
            return p.parse_expression(str);
        default:
            return NULL;
    }
}

pstr_t Parse::scan_lexical_symbol(pstr_t str)
{
    enum SymbolType type;

    do {
        type = get_symbol(str[0]);
        str++;
    } while (type == SYMBOL_WHITESPACE);

    return str - 1;
}

enum Parse::SymbolType Parse::get_symbol(char c)
{
    char dc = c | 0x20;

    if (c == '0') {
        return SYMBOL_NUMBER_ZERO;
    } else if ('1' <= c && c <= '7') {
        return SYMBOL_NUMBER_OCT;
    } else if (c == '8' || c == '9') {
        return SYMBOL_NUMBER_DEC;
    } else if ('A' <= c && c <= 'F') {
        return SYMBOL_ALPHABET_HEXUPPER;
    } else if ('a' <= c && c <= 'f') {
        return SYMBOL_ALPHABET_HEXLOWER;
    } else if (dc == 'x') {
        return SYMBOL_ALPHABET_X;
    } else if ('g' <= dc && dc <= 'z') {
        return SYMBOL_ALPHABET;
    } else if (c == '*') {
        return SYMBOL_OP_ASTERISK;
    } else if (c == '/') {
        return SYMBOL_OP_SLASH;
    } else if (c == '%') {
        return SYMBOL_OP_PERCENT;
    } else if (c == '+') {
        return SYMBOL_SIGN_PLUS;
    } else if (c == '+') {
        return SYMBOL_SIGN_PLUS;
    } else if (c == '-') {
        return SYMBOL_SIGN_MINUS;
    } else if (c == '(') {
        return SYMBOL_PAREN_LEFT;
    } else if (c == ')') {
        return SYMBOL_PAREN_RIGHT;
    } else if (c == '.') {
        return SYMBOL_DOT;
    } else if (c == '\0' || c == '\r' || c == '\n') {
        return SYMBOL_NULL;
    } else {
        printf("Unknown Symbol: %d\n", c);
        return SYMBOL_UNKNOWN;
    }
}
