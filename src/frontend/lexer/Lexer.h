#include <vector>
#include <unordered_map>

#include "Token.h"

class Lexer {
public:
    Lexer(std::string_view code)
    : source_code(code) 
    , current_position(0) {}

    std::vector<Token> tokenize();

private:
    void tokenize_number();

    std::string_view source_code;
    size_t current_position;
    std::vector<Token> tokens;

    inline static const std::unordered_map<std::string, TokenType> operator_table = {
        {"+", TokenType::Plus},
        {"-", TokenType::Minus},
    };
    
};