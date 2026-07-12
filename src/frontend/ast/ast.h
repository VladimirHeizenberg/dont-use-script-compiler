#pragma once


#include <memory>
#include <string>

#include "NodeVisitor.h"

#define AST_NODE_VISIT \
    void accept(NodeVisitor& v) override { v.visit(*this); }


/* interface */
struct Expression {
    virtual void accept(NodeVisitor&) = 0;
    virtual ~Expression() = default;
};


/* interface */
struct Statement {
    virtual void accept(NodeVisitor&) = 0;
    virtual ~Statement() = default;
};


enum BinaryExpressionType {
    kPlus,
    kMinus,
    kMultiply,
    kDivide,
};


/* -------------- Expressions -------------- */

struct ConstExpression : public Expression {
    ConstExpression(int v)
    : value(v) {}

    AST_NODE_VISIT

    int value;
};


struct BinaryExpression : public Expression {
    BinaryExpression(std::unique_ptr<Expression> l,
                     std::unique_ptr<Expression> r,
                     BinaryExpressionType t)
    : left(std::move(l))
    , right(std::move(r))
    , type(t) {}

    AST_NODE_VISIT

    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;
    BinaryExpressionType type;
};

/* -------------- Statements -------------- */

struct AssignStatement : public Statement {
    AssignStatement(std::string var_name, std::unique_ptr<Expression> expression)
    : name(std::move(var_name))
    , right(std::move(expression)) {}

    AST_NODE_VISIT
    
    std::string name;
    std::unique_ptr<Expression> right;
};
