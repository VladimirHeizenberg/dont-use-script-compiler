#pragma once

#include <vector>
#include <unordered_map>

#include "Token.h"

class Lexer {
public:
    Lexer(std::string_view code)
    : source_code_(code) 
    , current_position_(0) {}

    std::vector<Token> Tokenize();

private:
    void TokenizeNumber();
    void TokenizeOperator();
    void TokenizeIdentifier();

    void AddToken(TokenType type, std::string_view raw_str);
    void AddToken(TokenType type, std::string_view raw_str, size_t position);

    char Peek();
    char Eat();

    bool IsNumber(char current);
    bool IsOperator(char current);
    bool IsLetterOrLowLine(char current);

    std::string_view source_code_;
    size_t current_position_;
    std::vector<Token> tokens_;

    inline static const std::unordered_map<std::string, TokenType> kOperatorTable = {
        {"+", TokenType::kPlus},
        {"-", TokenType::kMinus},
        {"*", TokenType::kAsteriks},
        {"/", TokenType::kSlash},
        {"(", TokenType::kLeftParenthesis},
        {")", TokenType::kRightParenthesis},
        {"=", TokenType::kAssign},
        {";", TokenType::kSemicolon},
    };
    
    inline static const std::unordered_map<std::string, TokenType> kKeyWordsTable = {
        {"int", TokenType::kInt},
        {"float", TokenType::kFloat},
    };
};