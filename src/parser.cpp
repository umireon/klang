#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include "ast.h"
#include "parser.h"

enum symbol_type Parse::get_type_of_next_symbol(char c)
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
	} else if (c == '\0') {
		return SYMBOL_NULL;
	} else {
		printf("Unknown Symbol: %d\n", c);
		return SYMBOL_UNKNOWN;
	}
}

AstNode* Parse::parse_identifier(const char *str)
{
	ParseIdentifier p;
	return p.parse_identifier(str);
}

AstNode* Parse::parse_paren(const char *str)
{
	ParseParen p;
	return p.parse_paren(str);
}

AstNode* Parse::parse_number(const char *str)
{
	return pn.parse_number(str);
}

AstNode* Parse::parse_element(const char *str)
{
	AstNode *elem = new AstElement();
	elem->strhead = str;
	enum symbol_type type = get_type_of_next_symbol(str[0]);

	switch (type) {
	case SYMBOL_NUMBER_ZERO:
	case SYMBOL_NUMBER_OCT:
	case SYMBOL_NUMBER_DEC:
	case SYMBOL_SIGN_MINUS:
	case SYMBOL_SIGN_PLUS:
		elem->children.push_back(parse_number(str));
		break;
	case SYMBOL_PAREN_LEFT:
		elem->children.push_back(parse_paren(str));
		break;
	case SYMBOL_ALPHABET_HEXUPPER:
	case SYMBOL_ALPHABET_HEXLOWER:
	case SYMBOL_ALPHABET_X:
	case SYMBOL_ALPHABET:
		elem->children.push_back(parse_identifier(str));
		break;
	}

	elem->strtail = elem->children.at(0)->strtail;

	return elem;
}

AstNode* Parse::parse_term(const char *str)
{
	ParseTerm pt;
	return pt.parse_term(str);
}

AstNode* Parse::parse_expression(const char *str)
{
	ParseExpression p;
	return p.parse_expression(str);
}

AstNode* Parse::parse_statement(const char *str)
{
	AstNode *stmt;
	stmt = new AstStatement();
	stmt->strhead = str;

	enum symbol_type type = this->get_type_of_next_symbol(str[0]);

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
		stmt->children.push_back(this->parse_expression(str));
	}

	if (stmt->children.size() == 0) {
		stmt->strtail = str;
	} else {
		stmt->strtail = (*stmt->children.rbegin())->strtail;
	}

	return stmt;
}

AstNode* Parse::parse(const char *str)
{
	return this->parse_statement(str);
}
