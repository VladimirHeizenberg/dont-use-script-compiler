#include <iostream>

#include "frontend/lexer/Lexer.h"
#include "frontend/parser/Parser.h"
#include "frontend/executor/ExecutionNodeVisitor.h"

int main() {
    std::string code = "a = 1 + 234 - 3";
    Lexer lexer(code);
    auto res = lexer.Tokenize();
    Parser parser(std::move(res));
    auto parse_res = parser.Parse();
    ExecutionNodeVisitor executor;
    parse_res->accept(executor);
}