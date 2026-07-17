#pragma once

#include <memory>


struct ConstExpression;
struct VariableExpression;
struct BinaryExpression;


struct AssignStatement;
struct ComposeStatement;


class NodeVisitor {
public:
    virtual void Visit(ConstExpression&) = 0;
    virtual void Visit(VariableExpression&) = 0;
    virtual void Visit(BinaryExpression&) = 0;

    virtual void Visit(AssignStatement&) = 0;
    virtual void Visit(ComposeStatement&) = 0;
};