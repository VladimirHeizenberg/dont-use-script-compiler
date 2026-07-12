#pragma once

#include <memory>


struct ConstExpression;
struct BinaryExpression;


struct AssignStatement;


class NodeVisitor {
public:
    virtual void visit(ConstExpression&) = 0;
    virtual void visit(BinaryExpression&) = 0;

    virtual void visit(AssignStatement&) = 0;
};