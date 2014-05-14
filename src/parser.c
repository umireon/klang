#include <stdlib.h>
#include "parser.h"

enum symbol_type get_type_of_next_symbol(char c)
{
	if (c == '0') {
		return SYMBOL_ZERO;
	} else if ('1' <= c && c <= '9') {
		return SYMBOL_NONZERO;
	} else if (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z')) {
		return SYMBOL_ALPHABET;
	} else {
		return SYMBOL_UNKNOWN;
	}
}

int read_number_hex(const char *str)
{
	return 2;
}

int parse_number_hex_or_oct(const char *str)
{
	enum symbol_type type = get_type_of_next_symbol(str[1]);
	switch (type) {
	case SYMBOL_ALPHABET:
		if (str[1] == 'x' || str[1] == 'X') {
			return read_number_hex(str);
		}
		break;
	case SYMBOL_NONZERO:
	case SYMBOL_ZERO:
		break;
	}
	return 0;
}

int parse_number_dec(const char *str)
{
	return 1;
}

struct ast_node *parse_number(const char *str)
{
	struct ast_node *num = malloc(sizeof(struct ast_node));
	num->type = AST_NUMBER;
	num->num_of_child = 0;

	enum symbol_type type = get_type_of_next_symbol(str[0]);
	switch (type) {
	case SYMBOL_ZERO:
		num->value = parse_number_hex_or_oct(str);
		break;
	case SYMBOL_NONZERO:
		num->value = parse_number_dec(str);
		break;
	}

	return num;
}

struct ast_node *parse_statement(const char *str)
{
	struct ast_node *stmt;
	stmt = malloc(sizeof(struct ast_node));
	stmt->type = AST_STATEMENT;
	stmt->num_of_child = 0;

	enum symbol_type type = get_type_of_next_symbol(str[0]);

	switch (type) {
	case SYMBOL_ZERO:
	case SYMBOL_NONZERO:
		stmt->num_of_child++;
		stmt->children = malloc(sizeof(struct ast_node) * 1);
		struct ast_node *number = parse_number(str);
		stmt->children[0] = number;
	}

	return stmt;
}

struct ast_node *parse(const char *str)
{
	return parse_statement(str);
}
