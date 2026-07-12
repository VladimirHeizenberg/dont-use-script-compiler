#include "Lexer.h"

#include <vector>

#include "Token.h"
#include "LexerError.h"

std::vector<Token> Lexer::Tokenize() {
    tokens_.clear();

    while (current_position_ != source_code_.size()) {
        char current = Peek();
        if (std::isspace(current)) Eat();
        else if (IsNumber(current)) TokenizeNumber();
        else if (IsOperator(current)) TokenizeOperator();
        else if (IsLetterOrLowLine(current)) TokenizeIdentifier();
        else throw LexerError("Unexpected token at " + std::to_string(current_position_), current_position_);
    }

    AddToken(TokenType::kEof, source_code_.substr(current_position_ - 1, 1));

    return std::move(tokens_);
}


void Lexer::TokenizeNumber() {
    size_t start_position = current_position_;
    while (current_position_ < source_code_.size() && std::isdigit(Peek())) {
        Eat();
    }
    std::string_view raw_number = source_code_.substr(start_position, current_position_ - start_position);
    AddToken(TokenType::kNumber, raw_number, start_position);
}

void Lexer::TokenizeOperator() {
    char current = Eat();
    AddToken(kOperatorTable.at(std::string{current}), source_code_.substr(current_position_ - 1, 1));
}

void Lexer::TokenizeIdentifier() {
    std::string name;
    size_t start_position = current_position_;
    while (true) {
        char current = Peek();
        if (!(std::isdigit(current) || IsLetterOrLowLine(current))) {
            break;
        }
        name += current;
        Eat();
    }
    std::string_view raw_identifier = source_code_.substr(start_position, current_position_ - start_position);
    if (kKeyWordsTable.contains(name)) {
        return AddToken(kKeyWordsTable.at(name), raw_identifier, start_position);
    }
    AddToken(TokenType::kIdentifier, raw_identifier, start_position);
}

void Lexer::AddToken(TokenType type, std::string_view raw_str) {
    tokens_.emplace_back(raw_str, type, current_position_);
}

void Lexer::AddToken(TokenType type, std::string_view raw_str, size_t position) {
    tokens_.emplace_back(raw_str, type, position);
}

char Lexer::Peek() {
    return source_code_.at(current_position_);
}

char Lexer::Eat() {
    return source_code_.at(current_position_++);
}

bool Lexer::IsNumber(char current) {
    return std::isdigit(current);
}

bool Lexer::IsOperator(char current) {
    return kOperatorTable.contains(std::string{current});
}

bool Lexer::IsLetterOrLowLine(char current) {
    return (
        ('a' <= current && current <= 'z') ||
        ('A' <= current && current <= 'Z') ||
        (current == '_')
    );
}