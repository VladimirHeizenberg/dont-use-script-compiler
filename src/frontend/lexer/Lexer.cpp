#include "Lexer.h"

#include <vector>

#include "Token.h"

std::vector<Token> Lexer::tokenize() {
    tokens.clear();

    while (current_position != source_code.size()) {
        char current = source_code.at(current_position);
        if (is_number(current)) tokenize_number();
        else if (is_operator(current)) tokenize_operator();
        else current_position++;
    }

    add_token(TokenType::Eof, source_code.substr(current_position - 1, 1));

    return std::move(tokens);
}


void Lexer::tokenize_number() {
    size_t start_position = current_position;
    while (current_position < source_code.size() && std::isdigit(source_code.at(current_position))) {
        current_position++;
    }
    std::string_view raw_number = source_code.substr(start_position, current_position - start_position);
    add_token(TokenType::Number, raw_number, start_position);
}

void Lexer::tokenize_operator() {
    char current = source_code.at(current_position);
    add_token(operator_table.at(std::string{current}), source_code.substr(current_position, 1));
    current_position++;
}

void Lexer::add_token(TokenType type, std::string_view raw_str) {
    tokens.emplace_back(raw_str, type, current_position);
}

void Lexer::add_token(TokenType type, std::string_view raw_str, size_t position) {
    tokens.emplace_back(raw_str, type, position);
}

bool Lexer::is_number(char current) {
    return std::isdigit(current);
}

bool Lexer::is_operator(char current) {
    return operator_table.contains(std::string{current});
}