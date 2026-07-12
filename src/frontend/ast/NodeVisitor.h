#pragma once

#include <memory>


struct ConstExpression;
struct VariableExpression;
struct BinaryExpression;


struct AssignStatement;
struct ComposeStatement;


class NodeVisitor {
public:
    virtual void visit(ConstExpression&) = 0;
    virtual void visit(VariableExpression&) = 0;
    virtual void visit(BinaryExpression&) = 0;

    virtual void visit(AssignStatement&) = 0;
    virtual void visit(ComposeStatement&) = 0;
};