#include <string>

#include "TokenType.h"

struct TokenLocation {
    int line;
    int column;
};

class Token {
public:
    Token(std::string_view lexemme, TokenType t_type, TokenLocation t_location)
    : raw_lexemme(lexemme)
    , type(t_type)
    , location(t_location) {}

    [[nodiscard]] TokenType get_type() const {
        return type;
    }

    [[nodiscard]] std::string_view get_lexemme() const {
        return raw_lexemme;
    }

    [[nodiscard]] TokenLocation get_location() const {
        return location;
    }

private:
    std::string_view raw_lexemme;
    TokenType type;
    TokenLocation location;
};