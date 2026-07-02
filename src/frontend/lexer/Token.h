#pragma once

#include <string>

#include "TokenType.h"

class Token {
public:
    Token(std::string_view lexemme, TokenType type, size_t location)
    : raw_lexemme_(lexemme)
    , type_(type)
    , location_(location) {}

    [[nodiscard]] TokenType GetType() const {
        return type_;
    }

    [[nodiscard]] std::string_view GetLexemme() const {
        return raw_lexemme_;
    }

    [[nodiscard]] size_t GetLocation() const {
        return location_;
    }

private:
    std::string_view raw_lexemme_;
    TokenType type_;
    size_t location_;
};
