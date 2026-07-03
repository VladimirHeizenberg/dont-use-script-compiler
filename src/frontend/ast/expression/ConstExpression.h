#pragma once

#include "Expression.h"


class ConstExpression: public Expression {
public:
    ConstExpression(int value)
    : value_(value) {}

    int Evaluate() override {
        return value_;
    }
private:
    int value_;
};