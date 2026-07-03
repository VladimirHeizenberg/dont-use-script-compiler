#include <gtest/gtest.h>

#include "src/frontend/lexer/Lexer.h"
#include "src/frontend/parser/Parser.h"

TEST(ParserTestSuite, SimpleParserTest) {
    std::string code = "1 + 234 - 3";
    Lexer lexer(code);
    auto res = lexer.Tokenize();
    Parser parser(std::move(res));
    std::unique_ptr<Expression> parsed_result = parser.Parse();
    int expr_res = parsed_result->Evaluate();
    ASSERT_EQ(expr_res, 232);
}