#include <stdlib.h>
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
	} else if (c == '\0') {
		return SYMBOL_NULL;
	} else {
		printf("Unknown Symbol: %d\n", c);
		return SYMBOL_UNKNOWN;
	}
}

int read_number_oct(const char *str)
{
	char *p = str;
	enum symbol_type type;
	int val = 0;

	while (1) {
		type = get_type_of_next_symbol(p[0]);

		switch (type) {
		case SYMBOL_NUMBER_ZERO:
		case SYMBOL_NUMBER_OCT:
			val = val * 8 + p[0] - '0';
			p++;
			break;
		case SYMBOL_NUMBER_DEC:
		case SYMBOL_ALPHABET:
		case SYMBOL_ALPHABET_X:
		case SYMBOL_NULL:
			return val;
		}
	}
}

int read_number_hex(const char *str)
{
	char *p = str;
	enum symbol_type type;
	int val = 0;

	while (1) {
		type = get_type_of_next_symbol(p[0]);

		switch (type) {
		case SYMBOL_NUMBER_ZERO:
		case SYMBOL_NUMBER_OCT:
		case SYMBOL_NUMBER_DEC:
			val = val * 16 + p[0] - '0';
			p++;
			break;
		case SYMBOL_ALPHABET_HEXUPPER:
			val = val * 16 + p[0] - 'A' + 10;
			p++;
			break;
		case SYMBOL_ALPHABET_HEXLOWER:
			val = val * 16 + p[0] - 'a' + 10;
			p++;
			break;
		case SYMBOL_ALPHABET:
		case SYMBOL_ALPHABET_X:
		case SYMBOL_NULL:
			return val;
		}
	}
}

int read_number_dec(const char *str)
{
	char *p = str;
	enum symbol_type type;
	int val = 0;

	while (1) {
		type = get_type_of_next_symbol(p[0]);

		switch (type) {
		case SYMBOL_NUMBER_ZERO:
		case SYMBOL_NUMBER_OCT:
		case SYMBOL_NUMBER_DEC:
			val = val * 10 + p[0] - '0';
			p++;
			break;
		case SYMBOL_ALPHABET:
		case SYMBOL_ALPHABET_HEXUPPER:
		case SYMBOL_ALPHABET_HEXLOWER:
		case SYMBOL_ALPHABET_X:
		case SYMBOL_NULL:
			return val;
		}
	}
}

int read_number_hex_or_oct(const char *str)
{
	enum symbol_type type = get_type_of_next_symbol(str[1]);
	switch (type) {
	case SYMBOL_ALPHABET_X:
		return read_number_hex(str + 2);
	case SYMBOL_NUMBER_ZERO:
	case SYMBOL_NUMBER_OCT:
	case SYMBOL_NUMBER_DEC:
	case SYMBOL_NULL:
		return read_number_oct(str);
	}
}

struct ast_node *parse_number(const char *str)
{
	struct ast_node *num = malloc(sizeof(struct ast_node));
	num->type = AST_NUMBER;
	num->num_of_child = 0;

	enum symbol_type type = get_type_of_next_symbol(str[0]);
	switch (type) {
	case SYMBOL_NUMBER_ZERO:
		num->value = read_number_hex_or_oct(str);
		break;
	case SYMBOL_NUMBER_OCT:
	case SYMBOL_NUMBER_DEC:
		num->value = read_number_dec(str);
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
	case SYMBOL_NUMBER_ZERO:
	case SYMBOL_NUMBER_OCT:
	case SYMBOL_NUMBER_DEC:
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
