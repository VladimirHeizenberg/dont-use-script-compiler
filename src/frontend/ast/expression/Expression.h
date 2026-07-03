#pragma once

class Expression {
public:
    virtual int Evaluate() = 0;
    virtual ~Expression() = default;
};