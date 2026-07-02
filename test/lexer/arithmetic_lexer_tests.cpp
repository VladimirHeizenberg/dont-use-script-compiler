#include <gtest/gtest.h>

#include "src/frontend/lexer/Lexer.h"

TEST(LexerTestSuite, SimpleTest) {
    std::string code = "1 + 234 - 3";
    Lexer lexer(code);
    auto res = lexer.Tokenize();
    TokenType type = res[0].GetType();
    std::string_view lexemme = res[0].GetLexemme();
    ASSERT_EQ(type, TokenType::kNumber);
    ASSERT_EQ(lexemme, "1");
    type = res[1].GetType();
    lexemme = res[1].GetLexemme();
    ASSERT_EQ(type, TokenType::kPlus);
    ASSERT_EQ(lexemme, "+");
    type = res[2].GetType();
    lexemme = res[2].GetLexemme();
    ASSERT_EQ(type, TokenType::kNumber);
    ASSERT_EQ(lexemme, "234");
    type = res[3].GetType();
    lexemme = res[3].GetLexemme();
    ASSERT_EQ(type, TokenType::kMinus);
    ASSERT_EQ(lexemme, "-");
    type = res[4].GetType();
    lexemme = res[4].GetLexemme();
    ASSERT_EQ(type, TokenType::kNumber);
    ASSERT_EQ(lexemme, "3");
    type = res[5].GetType();
    ASSERT_EQ(type, TokenType::kEof);
}

TEST(LexerTestSuite, MinusTest) {
    std::string code = "-566";
    Lexer lexer(code);
    auto res = lexer.Tokenize();
    TokenType type = res[0].GetType();
    std::string_view lexemme = res[0].GetLexemme();
    ASSERT_EQ(type, TokenType::kMinus);
    ASSERT_EQ(lexemme, "-");
    type = res[1].GetType();
    lexemme = res[1].GetLexemme();
    ASSERT_EQ(type, TokenType::kNumber);
    ASSERT_EQ(lexemme, "566");
}