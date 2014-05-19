#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include "parser.h"

AstNode::~AstNode(void)
{
	int size = children.size();
	for (int i = 0; i < size; i++) {
		delete children.at(i);
	}
}

enum symbol_type get_type_of_next_symbol(char c)
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
	} else if (c == '+') {
		return SYMBOL_SIGN_PLUS;
	} else if (c == '+') {
		return SYMBOL_SIGN_PLUS;
	} else if (c == '-') {
		return SYMBOL_SIGN_MINUS;
	} else if (c == '\0') {
		return SYMBOL_NULL;
	} else {
		printf("Unknown Symbol: %d\n", c);
		return SYMBOL_UNKNOWN;
	}
}

int read_number_oct(const char **head)
{
	const char *str = *head;
	enum symbol_type type;
	int val = 0;

	while (1) {
		type = get_type_of_next_symbol(str[0]);

		switch (type) {
		case SYMBOL_NUMBER_ZERO:
		case SYMBOL_NUMBER_OCT:
			val = val * 8 + str[0] - '0';
			str++;
			break;
		default:
			*head = str;
			return val;
		}
	}
}

int read_number_hex(const char **head)
{
	const char *str = *head;
	enum symbol_type type;
	int val = 0;

	while (1) {
		type = get_type_of_next_symbol(str[0]);

		switch (type) {
		case SYMBOL_NUMBER_ZERO:
		case SYMBOL_NUMBER_OCT:
		case SYMBOL_NUMBER_DEC:
			val = val * 16 + str[0] - '0';
			str++;
			break;
		case SYMBOL_ALPHABET_HEXUPPER:
			val = val * 16 + str[0] - 'A' + 10;
			str++;
			break;
		case SYMBOL_ALPHABET_HEXLOWER:
			val = val * 16 + str[0] - 'a' + 10;
			str++;
			break;
		default:
			*head = str;
			return val;
		}
	}
}

int read_number_dec(const char **head)
{
	const char *str = *head;
	enum symbol_type type;
	int val = 0;

	while (1) {
		type = get_type_of_next_symbol(str[0]);

		switch (type) {
		case SYMBOL_NUMBER_ZERO:
		case SYMBOL_NUMBER_OCT:
		case SYMBOL_NUMBER_DEC:
			val = val * 10 + str[0] - '0';
			str++;
			break;
		default:
			*head = str;
			return val;
		}
	}
}

int read_number_hex_or_oct(const char **head)
{
	const char *str = *head;
	enum symbol_type type = get_type_of_next_symbol(str[0]);
	int val;

	switch (type) {
	case SYMBOL_ALPHABET_X:
		str++;
		val = read_number_hex(&str);
		break;
	case SYMBOL_NUMBER_OCT:
	case SYMBOL_NUMBER_DEC:
		val = read_number_oct(&str);
		break;
	default:
		val = 0;
	}

	*head = str;
	return val;
}

int read_number_signed(const char **head)
{
	const char *str = *head;
	enum symbol_type type = get_type_of_next_symbol(str[0]);
	int val;

	switch (type) {
	case SYMBOL_NUMBER_ZERO:
		str++;
		val = read_number_hex_or_oct(&str);
		break;
	case SYMBOL_NUMBER_OCT:
	case SYMBOL_NUMBER_DEC:
		val = read_number_dec(&str);
		break;
	case SYMBOL_SIGN_PLUS:
		str++;
		val = read_number_signed(&str);
		break;
	case SYMBOL_SIGN_MINUS:
		str++;
		val = -read_number_signed(&str);
		break;
	}

	*head = str;
	return val;
}

AstNode* parse_number(const char *str)
{
	AstNode *stub, *unknown;
	AstNode *num = new AstNode();
	num->type = AST_NUMBER;
	num->strhead = str;

	enum symbol_type type = get_type_of_next_symbol(str[0]);
	switch (type) {
	case SYMBOL_NUMBER_ZERO:
		str++;
		num->value = read_number_hex_or_oct(&str);
		break;
	case SYMBOL_NUMBER_OCT:
	case SYMBOL_NUMBER_DEC:
		num->value = read_number_dec(&str);
		break;
	case SYMBOL_SIGN_PLUS:
	case SYMBOL_SIGN_MINUS:
		num->value = read_number_signed(&str);
		break;
	case SYMBOL_NULL:
		stub = new AstNode();
		stub->type = AST_STUB;
		stub->strhead = str;

		unknown = new AstNode();
		unknown->type = AST_UNKNOWN;
		unknown->strhead = str;
		str++;
		unknown->strtail = str;
		stub->children.push_back(unknown);

		return stub;
	default:
		stub = new AstNode();
		stub->type = AST_STUB;
		stub->strhead = str;

		unknown = new AstNode();
		unknown->type = AST_UNKNOWN;
		unknown->strhead = str;
		str++;
		unknown->strtail = str;
		stub->children.push_back(unknown);

		num = parse_number(str);
		stub->children.push_back(num);
		stub->strtail = num->strtail;
		return stub;
	}

	num->strtail = str;

	return num;
}

AstNode* parse_term(const char *str)
{
	AstNode *term = new AstNode();
	AstNode *mul, *parent, *num;
	term->type = AST_TERM;
	term->strhead = str;

	enum symbol_type type = get_type_of_next_symbol(str[0]);
	switch (type) {
	case SYMBOL_NUMBER_ZERO:
	case SYMBOL_NUMBER_OCT:
	case SYMBOL_NUMBER_DEC:
	case SYMBOL_SIGN_MINUS:
	case SYMBOL_SIGN_PLUS:
		term->children.push_back(parse_number(str));
		str = term->children.at(0)->strtail;
		parent = term;

		while (1) {
			type = get_type_of_next_symbol(str[0]);
			switch (type) {
			case SYMBOL_OP_ASTERISK:
				mul = new AstNode();
				mul->type = AST_MULTIPLICATION;
				mul->strhead = str;
				mul->children.push_back(parent->children.at(0));
				parent->children.pop_back();
				str++;
				mul->children.push_back(parse_number(str));
				parent->children.push_back(mul);
				mul->strtail = term->strtail = str = mul->children.at(1)->strtail;
				break;
			case SYMBOL_OP_SLASH:
				mul = new AstNode();
				mul->type = AST_DIVISION;
				mul->strhead = str;
				mul->children.push_back(parent->children.at(0));
				parent->children.pop_back();
				str++;
				mul->children.push_back(parse_number(str));
				parent->children.push_back(mul);
				mul->strtail = term->strtail = str = mul->children.at(1)->strtail;
				break;
			default:
				return term;
			}
		}
	}

	return term;
}

AstNode* parse_statement(const char *str)
{
	AstNode *stmt;
	stmt = new AstNode();
	stmt->type = AST_STATEMENT;
	stmt->strhead = str;

	enum symbol_type type = get_type_of_next_symbol(str[0]);

	switch (type) {
	case SYMBOL_NUMBER_ZERO:
	case SYMBOL_NUMBER_OCT:
	case SYMBOL_NUMBER_DEC:
	case SYMBOL_SIGN_MINUS:
	case SYMBOL_SIGN_PLUS:
		stmt->children.push_back(parse_term(str));
	}

	if (stmt->children.size() == 0) {
		stmt->strtail = str;
	} else {
		stmt->strtail = (*stmt->children.rbegin())->strtail;
	}

	return stmt;
}

AstNode* parse(const char *str)
{
	return parse_statement(str);
}
