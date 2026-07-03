#include "Parser.h"

Parser::Parser(std::vector<Token> tokens) 
    : tokens_(std::move(tokens)), current_(0) {}

std::unique_ptr<Expression> Parser::Parse() {
    if (IsAtEnd()) {
        return nullptr;
    }
    
    auto expr = ParseExpression();
    
    if (!IsAtEnd() && Peek().GetType() != TokenType::kEof) {
        throw Error(Peek(), "Unexpected token after expression");
    }
    
    return expr;
}

std::unique_ptr<Expression> Parser::ParseExpression() {
    return ParseAddSub();
}

std::unique_ptr<Expression> Parser::ParseAddSub() {
    auto expr = ParseMulDiv();

    while (Match(TokenType::kPlus) || Match(TokenType::kMinus)) {
        Token operatorToken = Previous();
        auto right = ParseMulDiv();
        
        BinaryExpressionType type = (operatorToken.GetType() == TokenType::kPlus) 
                                    ? BinaryExpressionType::kPlus 
                                    : BinaryExpressionType::kMinus;
        
        expr = std::make_unique<BinaryExpression>(type, std::move(expr), std::move(right));
    }

    return expr;
}

std::unique_ptr<Expression> Parser::ParseMulDiv() {
    auto expr = ParsePrimary();

    while (Match(TokenType::kAsteriks) || Match(TokenType::kSlash)) {
        Token operatorToken = Previous();
        auto right = ParsePrimary();
        
        BinaryExpressionType type = (operatorToken.GetType() == TokenType::kAsteriks) 
                                    ? BinaryExpressionType::kMultiply 
                                    : BinaryExpressionType::kDivide;
        
        expr = std::make_unique<BinaryExpression>(type, std::move(expr), std::move(right));
    }

    return expr;
}

std::unique_ptr<Expression> Parser::ParsePrimary() {
    if (Match(TokenType::kNumber)) {
        Token numberToken = Previous();
        int value = 0;
        auto lexemme = numberToken.GetLexemme();
        
        auto [ptr, ec] = std::from_chars(lexemme.data(), lexemme.data() + lexemme.size(), value);
        if (ec != std::errc()) {
            throw Error(numberToken, "Invalid number format");
        }
        
        return std::make_unique<ConstExpression>(value);
    }

    if (Match(TokenType::kLeftParenthesis)) {
        auto expr = ParseExpression();
        Check(TokenType::kRightParenthesis, "Expected ')' after expression");
        return expr;
    }

    throw Error(Peek(), "Expected number or '('");
}

bool Parser::Match(TokenType type) {
    if (CheckType(type)) {
        Advance();
        return true;
    }
    return false;
}

Token Parser::Check(TokenType type, const std::string& errorMessage) {
    if (CheckType(type)) {
        return Advance();
    }
    throw Error(Peek(), errorMessage);
}

bool Parser::CheckType(TokenType type) const {
    if (IsAtEnd()) return false;
    return Peek().GetType() == type;
}

Token Parser::Advance() {
    if (!IsAtEnd()) current_++;
    return Previous();
}

Token Parser::Peek() const {
    return tokens_[current_];
}

Token Parser::Previous() const {
    return tokens_[current_ - 1];
}

bool Parser::IsAtEnd() const {
    return Peek().GetType() == TokenType::kEof || current_ >= tokens_.size();
}

ParseError Parser::Error(const Token& token, const std::string& message) const {
    std::string full_message = message + ". ";
    if (token.GetType() == TokenType::kEof) {
        full_message += "Found EOF at location " + std::to_string(token.GetLocation());
    } else {
        full_message += "Found '" + std::string(token.GetLexemme()) + 
                        "' at location " + std::to_string(token.GetLocation());
    }
    return ParseError(full_message);
}