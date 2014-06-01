#include <string>

#include "ast/AstNode.h"

std::string AstNode::get_string() {
    return std::string(strhead, strtail);
}
