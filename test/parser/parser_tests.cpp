#include <gtest/gtest.h>

#include "src/frontend/lexer/Lexer.h"
#include "src/frontend/parser/Parser.h"
#include "src/frontend/executor/ExecutionNodeVisitor.h"

TEST(ParserTestSuite, SimpleParserTest) {
    std::string code = "a = 1 + 234 - 3";
    Lexer lexer(code);
    auto res = lexer.Tokenize();
    Parser parser(std::move(res));
    auto parse_res = parser.Parse();
    ExecutionNodeVisitor executor;
    parse_res->accept(executor);
    int result = executor.GetResByName("a");
    ASSERT_EQ(result, 232);
}

TEST(ParserTestSuite, SimpleParserTest2) {
    std::string code = "a = 2 + 2 * 2";
    Lexer lexer(code);
    auto res = lexer.Tokenize();
    Parser parser(std::move(res));
    auto parse_res = parser.Parse();
    ExecutionNodeVisitor executor;
    parse_res->accept(executor);
    int result = executor.GetResByName("a");
    ASSERT_EQ(result, 6);
}

TEST(ParserTestSuite, SimpleParserTest3) {
    std::string code = "a = (2 + 2) * 2";
    Lexer lexer(code);
    auto res = lexer.Tokenize();
    Parser parser(std::move(res));
    auto parse_res = parser.Parse();
    ExecutionNodeVisitor executor;
    parse_res->accept(executor);
    int result = executor.GetResByName("a");
    ASSERT_EQ(result, 8);
}