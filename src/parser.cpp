#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "parser.h"

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

struct ast_node *parse_number(const char *str)
{
	struct ast_node *num = (struct ast_node*)malloc(sizeof(struct ast_node));
	num->type = AST_NUMBER;
	num->num_of_child = 0;
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
	}

	num->strtail = str;

	return num;
}

struct ast_node *parse_term(const char *str)
{
	struct ast_node *term = (struct ast_node*)malloc(sizeof(struct ast_node));
	struct ast_node *mul, *parent;
	term->type = AST_TERM;
	term->num_of_child = 0;

	enum symbol_type type = get_type_of_next_symbol(str[0]);
	switch (type) {
	case SYMBOL_NUMBER_ZERO:
	case SYMBOL_NUMBER_OCT:
	case SYMBOL_NUMBER_DEC:
	case SYMBOL_SIGN_MINUS:
	case SYMBOL_SIGN_PLUS:
		term->num_of_child = 1;
		term->children = (struct ast_node**)malloc(sizeof(struct ast_node*) * term->num_of_child);
		term->children[0] = parse_number(str);
		str = term->children[0]->strtail;
		parent = term;

		while (1) {
			type = get_type_of_next_symbol(str[0]);
			switch (type) {
			case SYMBOL_OP_ASTERISK:
				str++;
				mul = (struct ast_node*)malloc(sizeof(struct ast_node));
				mul->type = AST_MULTIPLICATION;
				mul->num_of_child = 2;
				mul->children = (struct ast_node**)malloc(sizeof(struct ast_node*) * mul->num_of_child);
				mul->children[0] = parent->children[0];
				mul->children[1] = parse_number(str);
				parent->children[0] = mul;
				str = mul->children[1]->strtail;
				break;
			case SYMBOL_OP_SLASH:
				str++;
				mul = (struct ast_node*)malloc(sizeof(struct ast_node));
				mul->type = AST_DIVISION;
				mul->num_of_child = 2;
				mul->children = (struct ast_node**)malloc(sizeof(struct ast_node*) * mul->num_of_child);
				mul->children[0] = parent->children[0];
				mul->children[1] = parse_number(str);
				parent->children[0] = mul;
				str = mul->children[1]->strtail;
				break;
			default:
				return term;
			}
		}
	}

	return term;
}

struct ast_node *parse_statement(const char *str)
{
	struct ast_node *stmt;
	stmt = (struct ast_node*)malloc(sizeof(struct ast_node));
	stmt->type = AST_STATEMENT;
	stmt->num_of_child = 0;

	enum symbol_type type = get_type_of_next_symbol(str[0]);

	switch (type) {
	case SYMBOL_NUMBER_ZERO:
	case SYMBOL_NUMBER_OCT:
	case SYMBOL_NUMBER_DEC:
	case SYMBOL_SIGN_MINUS:
	case SYMBOL_SIGN_PLUS:
		stmt->num_of_child++;
		stmt->children = (struct ast_node**)malloc(sizeof(struct ast_node*) * 1);
		struct ast_node *term = parse_term(str);
		stmt->children[0] = term;
	}

	return stmt;
}

struct ast_node *parse(const char *str)
{
	return parse_statement(str);
}
