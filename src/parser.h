#include <vector>

enum node_type {
	AST_STATEMENT,
	AST_NUMBER,
	AST_TERM,
	AST_MULTIPLICATION,
	AST_DIVISION,
	AST_STUB,
	AST_UNKNOWN,
	AST_ADDITION,
	AST_SUBTRACTION,
	AST_PAREN,
	AST_PAREN_LEFT,
	AST_PAREN_RIGHT,
	AST_EXPRESSION,
	AST_ELEMENT
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
	SYMBOL_PAREN_LEFT,
	SYMBOL_PAREN_RIGHT,
	SYMBOL_NULL,
	SYMBOL_UNKNOWN
};

class AstNode
{
public:
	enum node_type type;
	const char *strhead;
	const char *strtail;
	std::vector<AstNode*> children;
	int value;
	~AstNode();
};

int read_number_oct(const char **head);
int read_number_hex(const char **head);
int read_number_dec(const char **head);
int read_number_hex_or_oct(const char **head);
int read_number_signed(const char **head);

AstNode* parse(const char *str);
AstNode* parse_statement(const char *str);
AstNode* parse_expression(const char *str);
AstNode* parse_term(const char *str);
AstNode* parse_paren(const char *str);
AstNode* parse_number(const char *str);
