#include <gtest/gtest.h>

#include "src/frontend/lexer/Lexer.h"

TEST(LexerTestSuite, SimpleTest) {
    std::string code = "1 + 234 - 3";
    Lexer lexer(code);
    auto res = lexer.tokenize();
    TokenType type = res[0].get_type();
    std::string_view lexemme = res[0].get_lexemme();
    ASSERT_EQ(type, TokenType::Number);
    ASSERT_EQ(lexemme, "1");
    type = res[1].get_type();
    lexemme = res[1].get_lexemme();
    ASSERT_EQ(type, TokenType::Plus);
    ASSERT_EQ(lexemme, "+");
    type = res[2].get_type();
    lexemme = res[2].get_lexemme();
    ASSERT_EQ(type, TokenType::Number);
    ASSERT_EQ(lexemme, "234");
    type = res[3].get_type();
    lexemme = res[3].get_lexemme();
    ASSERT_EQ(type, TokenType::Minus);
    ASSERT_EQ(lexemme, "-");
    type = res[4].get_type();
    lexemme = res[4].get_lexemme();
    ASSERT_EQ(type, TokenType::Number);
    ASSERT_EQ(lexemme, "3");
    type = res[5].get_type();
    ASSERT_EQ(type, TokenType::Eof);
}

TEST(LexerTestSuite, MinusTest) {
    std::string code = "-566";
    Lexer lexer(code);
    auto res = lexer.tokenize();
    TokenType type = res[0].get_type();
    std::string_view lexemme = res[0].get_lexemme();
    ASSERT_EQ(type, TokenType::Minus);
    ASSERT_EQ(lexemme, "-");
    type = res[1].get_type();
    lexemme = res[1].get_lexemme();
    ASSERT_EQ(type, TokenType::Number);
    ASSERT_EQ(lexemme, "566");
}