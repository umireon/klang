struct ast_node {
    int type;
    int value;
    int num_of_child;
    struct ast_node **children;
};

struct ast_node *parse(const char *str);
struct ast_node *parse_statement(const char *str);
struct ast_node *parse_number(const char *str);

#define AST_STATEMENT 1000
#define AST_NUMBER 1001
#define TOKEN_NUMBER 2000

enum symbol_type {
	SYMBOL_ZERO,
	SYMBOL_NONZERO,
	SYMBOL_ALPHABET,
	SYMBOL_UNKNOWN
};
