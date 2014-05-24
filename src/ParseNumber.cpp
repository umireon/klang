#include <iostream>
#include <sstream>

#include "ast.h"
#include "parser.h"

AstNumber* ParseNumber::parse_number(const char* str)
{
	AstNumber* num;
    
	enum symbol_type type = get_symbol(str[0]);
	switch (type) {
        case SYMBOL_NUMBER_ZERO:
            num = read_number_hex_or_oct(str+1);
            break;
        case SYMBOL_NUMBER_OCT:
        case SYMBOL_NUMBER_DEC:
            num = read_number_dec_or_float(str);
            break;
        case SYMBOL_SIGN_PLUS:
        case SYMBOL_SIGN_MINUS:
            num = read_number_signed(str+1);
            break;
        default:
            std::ostringstream os;
            os << "Unexpected character: " << str[0] << std::endl;
            throw std::invalid_argument(os.str());
	}
    
	num->strhead = str;
    
	return num;
}

AstNumber* ParseNumber::read_number_signed(const char *str)
{
	enum symbol_type type = get_symbol(str[0]);
    
	switch (type) {
        case SYMBOL_NUMBER_ZERO:
            return read_number_hex_or_oct(str + 1);
        case SYMBOL_NUMBER_OCT:
        case SYMBOL_NUMBER_DEC:
            return read_number_dec_or_float(str);
        default:
            std::ostringstream os;
            os << "Unexpected character: " << str[0] << std::endl;
            throw std::invalid_argument(os.str());
	}
}

AstInteger* ParseNumber::read_number_hex_or_oct(const char* str)
{
	enum symbol_type type = get_symbol(str[0]);
    
	switch (type) {
        case SYMBOL_ALPHABET_X:
            return read_number_hex(str+1);
        default:
            return read_number_oct(str);
	}
}

AstHexdecimal* ParseNumber::read_number_hex(const char *str)
{
	AstHexdecimal *hex = new AstHexdecimal();
    
	while (1) {
		enum symbol_type type = get_symbol(str[0]);
        
		switch (type) {
            case SYMBOL_NUMBER_ZERO:
            case SYMBOL_NUMBER_OCT:
            case SYMBOL_NUMBER_DEC:
            case SYMBOL_ALPHABET_HEXUPPER:
            case SYMBOL_ALPHABET_HEXLOWER:
                str++;
                break;
            default:
                hex->strtail = str;
                return hex;
		}
	}
}

AstOctal* ParseNumber::read_number_oct(const char *str)
{
	AstOctal *oct = new AstOctal();
    
	while (1) {
		enum symbol_type type = get_symbol(str[0]);
        
		switch (type) {
            case SYMBOL_NUMBER_ZERO:
            case SYMBOL_NUMBER_OCT:
                str++;
                break;
            default:
                oct->strtail = str;
                return oct;
		}
	}
}

AstNumber* ParseNumber::read_number_dec_or_float(const char* str)
{
	while (1) {
		enum symbol_type type = get_symbol(str[0]);
        
		switch (type) {
            case SYMBOL_NUMBER_ZERO:
            case SYMBOL_NUMBER_OCT:
            case SYMBOL_NUMBER_DEC:
                str++;
                break;
            case SYMBOL_DOT:
                return read_number_float(str + 1);
            default:
                return read_number_dec(str);
		}
	}
}

AstDecimal* ParseNumber::read_number_dec(const char* str)
{
	AstDecimal *dec = new AstDecimal();
	dec->strtail = str;
	return dec;
}

AstFloat* ParseNumber::read_number_float(const char *str)
{
	AstFloat *flt = new AstFloat();
    
	while (1) {
		enum symbol_type type = get_symbol(str[0]);
        
		switch (type) {
            case SYMBOL_NUMBER_ZERO:
            case SYMBOL_NUMBER_OCT:
            case SYMBOL_NUMBER_DEC:
                str++;
                break;
            default:
                flt->strtail = str;
                return flt;
		}
	}
}

enum symbol_type ParseNumber::get_symbol(char c)
{
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
	} else if (c == 'x' || c == 'X') {
		return SYMBOL_ALPHABET_X;
	} else if (c == '.') {
		return SYMBOL_DOT;
	} else if (c == '+') {
		return SYMBOL_SIGN_PLUS;
	} else if (c == '-') {
		return SYMBOL_SIGN_MINUS;
	} else if (c == '\0') {
		return SYMBOL_NULL;
	} else {
		return SYMBOL_FOLLOW;
	}
}

