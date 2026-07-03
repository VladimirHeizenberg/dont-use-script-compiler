#pragma once

#include <memory>

#include "Expression.h"

enum class BinaryExpressionType {
    kPlus,
    kMinus,
    kMultiply,
    kDivide,
};

class BinaryExpression : public Expression {
public:
    BinaryExpression(BinaryExpressionType type, 
                     std::unique_ptr<Expression> left,
                     std::unique_ptr<Expression> right)
    : type_(type)
    , left_(std::move(left))
    , right_(std::move(right)) {}

    int Evaluate() override {
        switch (type_) {
            case BinaryExpressionType::kPlus: return left_->Evaluate() + right_->Evaluate();
            case BinaryExpressionType::kMinus: return left_->Evaluate() - right_->Evaluate();
            case BinaryExpressionType::kMultiply: return left_->Evaluate() * right_->Evaluate();
            case BinaryExpressionType::kDivide: return left_->Evaluate() / right_->Evaluate();
        }
    }
private:
    BinaryExpressionType type_;

    std::unique_ptr<Expression> left_;
    std::unique_ptr<Expression> right_;
};