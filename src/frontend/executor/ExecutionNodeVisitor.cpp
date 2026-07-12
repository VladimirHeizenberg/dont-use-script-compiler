#include "ExecutionNodeVisitor.h"

#include "ast/ast.h"


void ExecutionNodeVisitor::visit(ConstExpression& expression) {
    stack_.push_back(expression.value);
}


void ExecutionNodeVisitor::visit(VariableExpression& expression) {
    stack_.push_back(variables_table_[expression.name]);
}


void ExecutionNodeVisitor::visit(BinaryExpression& expression) {
    expression.left->accept(*this);
    expression.right->accept(*this);
    int right_expr_result = stack_.back();
    stack_.pop_back();
    int left_expr_result = stack_.back();
    stack_.pop_back();
    switch (expression.type)
    {
    case BinaryExpressionType::kPlus:
        stack_.push_back(left_expr_result + right_expr_result);
        break;
    case BinaryExpressionType::kMinus:
        stack_.push_back(left_expr_result - right_expr_result);
        break;
    case BinaryExpressionType::kMultiply:
        stack_.push_back(left_expr_result * right_expr_result);
        break;
    case BinaryExpressionType::kDivide:
        stack_.push_back(left_expr_result / right_expr_result);
        break;
    }
}


void ExecutionNodeVisitor::visit(AssignStatement& statement) {
    statement.right->accept(*this);
    variables_table_[statement.name] = stack_.back();
    stack_.pop_back();
}


void ExecutionNodeVisitor::visit(ComposeStatement& statements) {
    for (auto& statement : statements) {
        statement->accept(*this);
    }
}

int ExecutionNodeVisitor::GetResByName(std::string name) {
    return variables_table_[name];
}