#pragma once

#include <charconv>
#include <vector>
#include <memory>

#include "../ast/ast.h"
#include "../lexer/Lexer.h"
#include "ParseError.h"

class Parser {
public:
    explicit Parser(std::vector<Token> tokens);

    std::unique_ptr<Expression> Parse();

private:
    std::unique_ptr<Expression> ParseExpression();
    std::unique_ptr<Expression> ParseAddSub();
    std::unique_ptr<Expression> ParseMulDiv();
    std::unique_ptr<Expression> ParsePrimary();

    bool Match(TokenType type);
    Token Check(TokenType type, const std::string& errorMessage);
    bool CheckType(TokenType type) const;
    Token Advance();
    Token Peek() const;
    Token Previous() const;
    bool IsAtEnd() const;

    ParseError Error(const Token& token, const std::string& message) const;

    std::vector<Token> tokens_;
    size_t current_;
};