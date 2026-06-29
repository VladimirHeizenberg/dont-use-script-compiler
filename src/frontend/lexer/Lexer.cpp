#include "Lexer.h"

#include <vector>

#include "Token.h"

std::vector<Token> Lexer::tokenize() {
    tokens.clear();
}


void Lexer::tokenize_number() {
    std::string number;
    number.reserve(32);
    while (std::isdigit(source_code.at(current_position))) {
        number.push_back(source_code.at(current_position));
        current_position++;
    }
}

void Lexer::skip_whitespaces() {
    while (std::isspace(source_code.at(current_position))) {
        
    }
}