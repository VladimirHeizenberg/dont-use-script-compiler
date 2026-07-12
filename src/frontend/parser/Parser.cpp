#include "Parser.h"

#include <string>

#include "ParseError.h"
#include "ast/ast.h"

Parser::Parser(std::vector<Token> tokens)
: tokens_(std::move(tokens))
, current_position_(0) {}

std::unique_ptr<Statement> Parser::Parse() {
    return ParseAssign();
}

std::unique_ptr<Statement> Parser::ParseAssign() {
    if (!Check(TokenType::kIdentifier)) {
        throw ParseError("not identifier");
    }
    std::string name = std::string(tokens_[current_position_++].GetLexemme());
    if (!Match(TokenType::kAssign)) {
        throw ParseError("not assign");
    }
    auto expr = ParseExpression();
    return std::make_unique<AssignStatement>(name, std::move(expr));
}

std::unique_ptr<Expression> Parser::ParseExpression() {
    return ParsePlusMinus();
}

std::unique_ptr<Expression> Parser::ParsePlusMinus() {
    std::unique_ptr<Expression> left = ParseMultDiv();
    while (Check(TokenType::kPlus) || Check(TokenType::kMinus)) {
        if (Match(TokenType::kPlus)) {
            std::unique_ptr<Expression> right = ParseMultDiv();
            left = std::make_unique<BinaryExpression>(std::move(left), std::move(right), BinaryExpressionType::kPlus);
        } else if (Match(TokenType::kMinus)) {
            std::unique_ptr<Expression> right = ParseMultDiv();
            left = std::make_unique<BinaryExpression>(std::move(left), std::move(right), BinaryExpressionType::kMinus);
        }
    }
    return left;
}

std::unique_ptr<Expression> Parser::ParseMultDiv() {
    std::unique_ptr<Expression> left = ParseLiteral();
    while (Check(TokenType::kAsteriks) || Check(TokenType::kSlash)) {
        if (Match(TokenType::kAsteriks)) {
            std::unique_ptr<Expression> right = ParseLiteral();
            left = std::make_unique<BinaryExpression>(std::move(left), std::move(right), BinaryExpressionType::kMultiply);
        } else if (Match(TokenType::kSlash)) {
            std::unique_ptr<Expression> right = ParseLiteral();
            left = std::make_unique<BinaryExpression>(std::move(left), std::move(right), BinaryExpressionType::kDivide);
        }
    }
    return left;
}

std::unique_ptr<Expression> Parser::ParseLiteral() {
    if (Match(TokenType::kLeftParenthesis)) {
        std::unique_ptr<Expression> inner_expr = ParseExpression();
        if (!Check(TokenType::kRightParenthesis)) {
            throw ParseError("unclosed parenthesis");
        }
        current_position_++;
        return inner_expr;
    }
    if (Check(TokenType::kNumber)) {
        try {
            int num = std::stoi(std::string(tokens_[current_position_].GetLexemme()));
            std::unique_ptr<Expression> number = std::make_unique<ConstExpression>(num);
            current_position_++;
            return number;
        } catch (std::invalid_argument& e) {
            throw ParseError("invalid argument");
        } catch (std::out_of_range& e) {
            throw ParseError("out of range number");
        }
    }
    throw ParseError("unknown token" + std::to_string(current_position_));
}


bool Parser::Match(TokenType type) {
    if (Check(type)) {
        current_position_++;
        return true;
    }
    return false;
}

bool Parser::Check(TokenType type) {
    if (IsAtEnd()) return false;
    if (tokens_[current_position_].GetType() == type) {
        return true;
    }
    return false;
}

bool Parser::IsAtEnd() {
     return current_position_ >= tokens_.size() || 
           tokens_[current_position_].GetType() == TokenType::kEof;
}