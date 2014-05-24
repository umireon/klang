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

AstNode* Parse::parse_paren_right(const char *str)
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

AstNode* Parse::parse_paren_left(const char *str)
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

AstNode* Parse::parse_paren(const char *str)
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
	AstNode *term = new AstTerm();
	AstNode *mul, *parent, *num;
	term->strhead = str;

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
		AstNode *elem = this->parse_element(str);
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
			mul->children.push_back(this->parse_element(str));
			parent->children.push_back(mul);
			mul->strtail = term->strtail = str = mul->children.at(1)->strtail;
			break;
		case SYMBOL_OP_SLASH:
			mul = new AstDivision();
			mul->strhead = str;
			mul->children.push_back(parent->children.at(0));
			parent->children.pop_back();
			str++;
			mul->children.push_back(this->parse_element(str));
			parent->children.push_back(mul);
			mul->strtail = term->strtail = str = mul->children.at(1)->strtail;
			break;
		default:
			return term;
		}
	}

	return term;
}

AstNode* Parse::parse_expression(const char *str)
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
		expr->children.push_back(this->parse_term(str));
		expr->strtail = str = expr->children.at(0)->strtail;
		parent = expr;

		while (1) {
			type = this->get_type_of_next_symbol(str[0]);
			switch (type) {
			case SYMBOL_SIGN_PLUS:
				mul = new AstAddition();
				mul->strhead = str;
				mul->children.push_back(parent->children.at(0));
				parent->children.pop_back();
				str++;
				mul->children.push_back(this->parse_term(str));
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
				mul->children.push_back(this->parse_term(str));
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
