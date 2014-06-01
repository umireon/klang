#include <sstream>
#include <stdexcept>

#include "ast/AstIdentifier.h"

#include "parser/types.h"
#include "parser/ParseIdentifier.h"

AstIdentifier* ParseIdentifier::parse_identifier(pstr_t str)
{
	AstIdentifier *ident = new AstIdentifier();
	ident->strhead = str;
    
	enum SymbolType type = get_symbol(str[0]);
    
	switch (type) {
        case SYMBOL_ALPHABET_LOWER:
        case SYMBOL_ALPHABET_UPPER:
            str++;
            break;
        case SYMBOL_NUMBER:
        case SYMBOL_FOLLOW:
            std::ostringstream os;
            os << "Unexpected character: " << str[0] << std::endl;
            throw std::invalid_argument(os.str());
	}
    
	while (1) {
		type = get_symbol(str[0]);
        
		switch (type) {
            case SYMBOL_ALPHABET_LOWER:
            case SYMBOL_ALPHABET_UPPER:
            case SYMBOL_NUMBER:
                str++;
                break;
            case SYMBOL_FOLLOW:
                ident->strtail = str;
                return ident;
		}
	}
}

enum ParseIdentifier::SymbolType ParseIdentifier::get_symbol(char c)
{
	if ('0' <= c && c <= '9') {
		return SYMBOL_NUMBER;
	} else if ('A' <= c && c <= 'Z') {
		return SYMBOL_ALPHABET_UPPER;
	} else if ('a' <= c && c <= 'z') {
		return SYMBOL_ALPHABET_LOWER;
	} else {
		return SYMBOL_FOLLOW;
	}
}
