#include <string>

#include "ast.h"

std::string AstNode::get_string() {
    return std::string(strhead, strtail);
}
