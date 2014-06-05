#include <cstdlib>
#include <sstream>
#include <stdexcept>

#include "ast/AstNumber.h"
#include "ast/AstFloat.h"
#include "ast/AstDecimal.h"
#include "ast/AstHexdecimal.h"
#include "ast/AstOctal.h"

#include "parser/types.h"
#include "parser/SyntaxErrorHandler.h"
#include "parser/TokenNumber.h"

AstNumber* TokenNumber::parse_number(pstr_t str)
{
    AstNumber* num;

    enum SymbolType type = get_symbol(str);
    switch (type) {
        case SYMBOL_NUMBER_ZERO:
            num = read_number_hex_or_oct_or_float(str+1);
            break;
        case SYMBOL_NUMBER_OCT:
        case SYMBOL_NUMBER_DEC:
            num = read_number_dec_or_float(str);
            break;
        case SYMBOL_SIGN:
            num = read_number_signed(str+1);
            break;
        default:
            pstr_t recover = syntaxErrorHandler->invalid_char(str, __FUNCTION__);
            if (*recover != '\0') {
                return parse_number(recover);
            } else {
                AstInteger *nullnum = new AstInteger();
                nullnum->strtail = recover;
                return nullnum;
            }
    }

    num->strhead = str;
    num->save_value();

    return num;
}

AstNumber* TokenNumber::read_number_signed(pstr_t str)
{
    enum SymbolType type = get_symbol(str);

    switch (type) {
        case SYMBOL_NUMBER_ZERO:
            return read_number_hex_or_oct_or_float(str + 1);
        case SYMBOL_NUMBER_OCT:
        case SYMBOL_NUMBER_DEC:
            return read_number_dec_or_float(str);
        default:
            pstr_t recover = syntaxErrorHandler->invalid_char(str, __FUNCTION__);
            if (*recover != '\0') {
                return read_number_signed(recover);
            } else {
                AstInteger *nullnum = new AstInteger();
                nullnum->strtail = recover;
                return nullnum;
            }
    }
}

AstNumber* TokenNumber::read_number_hex_or_oct_or_float(pstr_t str)
{
    enum SymbolType type = get_symbol(str);

    switch (type) {
        case SYMBOL_ALPHABET_X:
            return read_number_hex(str+1);
        case SYMBOL_DOT:
            return read_number_float(str+1);
        default:
            return read_number_oct(str);
    }
}

AstHexdecimal* TokenNumber::read_number_hex(pstr_t str)
{
    AstHexdecimal *hex = new AstHexdecimal();

    while (1) {
        enum SymbolType type = get_symbol(str);

        switch (type) {
            case SYMBOL_NUMBER_ZERO:
            case SYMBOL_NUMBER_OCT:
            case SYMBOL_NUMBER_DEC:
            case SYMBOL_ALPHABET_HEX:
                str++;
                break;
            default:
                hex->strtail = str;
                return hex;
        }
    }
}

AstOctal* TokenNumber::read_number_oct(pstr_t str)
{
    AstOctal *oct = new AstOctal();

    while (1) {
        enum SymbolType type = get_symbol(str);

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

AstNumber* TokenNumber::read_number_dec_or_float(pstr_t str)
{
    while (1) {
        enum SymbolType type = get_symbol(str);

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

AstDecimal* TokenNumber::read_number_dec(pstr_t str)
{
    AstDecimal *dec = new AstDecimal();
    dec->strtail = str;
    return dec;
}

AstFloat* TokenNumber::read_number_float(pstr_t str)
{
    AstFloat *flt = new AstFloat();

    while (1) {
        enum SymbolType type = get_symbol(str);

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

enum TokenNumber::SymbolType TokenNumber::get_symbol(pstr_t str)
{
    if (str == line->end()) {
        return SYMBOL_FOLLOW;
    }
    
    char c = *str;
    
    if ('1' <= c && c <= '7') {
        return SYMBOL_NUMBER_OCT;
    } else if ('A' <= c && c <= 'F') {
        return SYMBOL_ALPHABET_HEX;
    } else if ('a' <= c && c <= 'f') {
        return SYMBOL_ALPHABET_HEX;
    }

    switch (c) {
        case '0':
            return SYMBOL_NUMBER_ZERO;
        case '8':
        case '9':
            return SYMBOL_NUMBER_DEC;
        case 'x':
        case 'X':
            return SYMBOL_ALPHABET_X;
        case '.':
            return SYMBOL_DOT;
        case '+':
        case '-':
            return SYMBOL_SIGN;
        default:
            return SYMBOL_FOLLOW;
    }
}
