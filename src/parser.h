#include <vector>

enum node_type {
	AST_STATEMENT,
	AST_NUMBER,
	AST_TERM,
	AST_MULTIPLICATION,
	AST_DIVISION
};

enum symbol_type {
	SYMBOL_NUMBER_ZERO,
	SYMBOL_NUMBER_OCT,
	SYMBOL_NUMBER_DEC,
	SYMBOL_OP_ASTERISK,
	SYMBOL_OP_SLASH,
	SYMBOL_SIGN_PLUS,
	SYMBOL_SIGN_MINUS,
	SYMBOL_ALPHABET,
	SYMBOL_ALPHABET_X,
	SYMBOL_ALPHABET_HEXUPPER,
	SYMBOL_ALPHABET_HEXLOWER,
	SYMBOL_NULL,
	SYMBOL_UNKNOWN
};

class AstNode
{
public:
	enum node_type type;
	const char *strhead;
	const char *strtail;
	std::vector<AstNode> children;
	int value;
};

AstNode& parse(const char *str);
AstNode& parse_statement(const char *str);
AstNode& parse_term(const char *str);
AstNode& parse_number(const char *str);
