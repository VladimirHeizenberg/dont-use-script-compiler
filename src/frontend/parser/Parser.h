#pragma once

#include <vector>
#include <memory>

#include "lexer/Token.h"
#include "ast/expression/Expression.h"

class Parser {
public:
    Parser(std::vector<Token> tokens);

    std::unique_ptr<Expression> Parse();

private:
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
