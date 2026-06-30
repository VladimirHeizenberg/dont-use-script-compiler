#include <gtest/gtest.h>

#include "src/frontend/lexer/Lexer.h"

TEST(LexerTestSuite, SimpleTest) {
    std::string code = "1 + 2 - 3";
    Lexer lexer(code);
    auto res = lexer.tokenize();
    TokenType type = res[0].get_type();
    ASSERT_EQ(type, TokenType::Number);
    type = res[1].get_type();
    ASSERT_EQ(type, TokenType::Plus);
    type = res[2].get_type();
    ASSERT_EQ(type, TokenType::Number);
    type = res[3].get_type();
    ASSERT_EQ(type, TokenType::Minus);
    type = res[4].get_type();
    ASSERT_EQ(type, TokenType::Number);
}