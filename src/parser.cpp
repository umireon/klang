#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include "ast.h"
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
	} else if (c == '(') {
		return SYMBOL_PAREN_LEFT;
	} else if (c == ')') {
		return SYMBOL_PAREN_RIGHT;
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

AstNode* parse_identifier(const char *str)
{
	AstNode *ident = new AstIdentifier();
	ident->strhead = str;

	enum symbol_type type;

	while (1) {
		type = get_type_of_next_symbol(str[0]);

		switch (type) {
		case SYMBOL_ALPHABET_HEXUPPER:
		case SYMBOL_ALPHABET_HEXLOWER:
		case SYMBOL_ALPHABET_X:
		case SYMBOL_ALPHABET:
		case SYMBOL_NUMBER_ZERO:
		case SYMBOL_NUMBER_OCT:
		case SYMBOL_NUMBER_DEC:
			str++;
			break;
		default:
			ident->strtail = str;
			return ident;
		}
	}
}

AstNode* parse_paren_right(const char *str)
{
	AstNode *stub, *unknown;
	AstNode *pright;

	enum symbol_type type = get_type_of_next_symbol(str[0]);
	switch (type) {
	case SYMBOL_PAREN_RIGHT:
		pright = new AstNode();
		pright->type = AST_PAREN_RIGHT;
		pright->strhead = str;
		str++;
		pright->strtail = str;
		return pright;
		break;
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

		pright = parse_paren_right(str);
		stub->children.push_back(pright);
		stub->strtail = pright->strtail;
		return stub;
	}
}

AstNode* parse_paren_left(const char *str)
{
	AstNode *stub, *unknown;
	AstNode *pleft = new AstNode();
	pleft->type = AST_PAREN_LEFT;
	pleft->strhead = str;

	enum symbol_type type = get_type_of_next_symbol(str[0]);
	switch (type) {
	case SYMBOL_PAREN_LEFT:
		str++;
		break;
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

		pleft = parse_paren_left(str);
		stub->children.push_back(pleft);
		stub->strtail = pleft->strtail;
		return stub;
	}

	pleft->strtail = str;

	return pleft;
}

AstNode* parse_paren(const char *str)
{
	AstNode *term = new AstParen();
	term->strhead = str;
	AstNode *pleft = parse_paren_left(str);
	term->children.push_back(pleft);
	str = pleft->strtail;

	AstNode *expr = parse_expression(str);
	term->children.push_back(expr);
	str = expr->strtail;

	AstNode *pright = parse_paren_right(str);
	term->children.push_back(pright);
	term->strtail = pright->strtail;
	return term;
}

AstNode* parse_number(const char *str)
{
	AstNode *stub, *unknown;
	AstNode *num = new AstNumber();
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

AstNode* parse_element(const char *str)
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

AstNode* parse_term(const char *str)
{
	AstNode *term = new AstTerm();
	AstNode *mul, *parent, *num;
	term->strhead = str;

	enum symbol_type type = get_type_of_next_symbol(str[0]);
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
		AstNode *elem = parse_element(str);
		term->children.push_back(elem);
		term->strtail = str = elem->strtail;
		parent = term;
		break;
	}

	while (1) {
		type = get_type_of_next_symbol(str[0]);
		switch (type) {
		case SYMBOL_OP_ASTERISK:
			mul = new AstMultiplication();
			mul->strhead = str;
			mul->children.push_back(parent->children.at(0));
			parent->children.pop_back();
			str++;
			mul->children.push_back(parse_element(str));
			parent->children.push_back(mul);
			mul->strtail = term->strtail = str = mul->children.at(1)->strtail;
			break;
		case SYMBOL_OP_SLASH:
			mul = new AstDivision();
			mul->strhead = str;
			mul->children.push_back(parent->children.at(0));
			parent->children.pop_back();
			str++;
			mul->children.push_back(parse_element(str));
			parent->children.push_back(mul);
			mul->strtail = term->strtail = str = mul->children.at(1)->strtail;
			break;
		default:
			return term;
		}
	}

	return term;
}

AstNode* parse_expression(const char *str)
{
	AstNode *expr = new AstExpression();
	AstNode *mul, *parent, *num;
	expr->strhead = str;

	enum symbol_type type = get_type_of_next_symbol(str[0]);
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
		expr->children.push_back(parse_term(str));
		expr->strtail = str = expr->children.at(0)->strtail;
		parent = expr;

		while (1) {
			type = get_type_of_next_symbol(str[0]);
			switch (type) {
			case SYMBOL_SIGN_PLUS:
				mul = new AstAddition();
				mul->strhead = str;
				mul->children.push_back(parent->children.at(0));
				parent->children.pop_back();
				str++;
				mul->children.push_back(parse_term(str));
				parent->children.push_back(mul);
				mul->strtail = expr->strtail = str = mul->children.at(1)->strtail;
				break;
			case SYMBOL_SIGN_MINUS:
				mul = new AstSubtraction();
				mul->type = AST_SUBTRACTION;
				mul->strhead = str;
				mul->children.push_back(parent->children.at(0));
				parent->children.pop_back();
				str++;
				mul->children.push_back(parse_term(str));
				parent->children.push_back(mul);
				mul->strtail = expr->strtail = str = mul->children.at(1)->strtail;
				break;
			default:
				return expr;
			}
		}
	}

	return expr;
}

AstNode* parse_statement(const char *str)
{
	AstNode *stmt;
	stmt = new AstStatement();
	stmt->strhead = str;

	enum symbol_type type = get_type_of_next_symbol(str[0]);

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
		stmt->children.push_back(parse_expression(str));
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
