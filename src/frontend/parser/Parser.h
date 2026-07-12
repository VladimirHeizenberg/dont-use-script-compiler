#pragma once

#include <vector>
#include <memory>

#include "lexer/Token.h"
#include "ast/ast.h"

class Parser {
public:
    Parser(std::vector<Token> tokens);

    std::unique_ptr<Statement> Parse();

private:
    std::unique_ptr<Statement> ParseAssign();

    std::unique_ptr<Expression> ParseExpression();

    std::unique_ptr<Expression> ParsePlusMinus();
    std::unique_ptr<Expression> ParseMultDiv();
    
    std::unique_ptr<Expression> ParseLiteral();

    bool Match(TokenType type); // eats token if matches
    bool Check(TokenType type); // doesn't

    bool IsAtEnd();

    std::vector<Token> tokens_;
    size_t current_position_;
};
