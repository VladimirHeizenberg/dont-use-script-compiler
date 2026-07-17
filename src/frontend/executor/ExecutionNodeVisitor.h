#pragma once

#include <vector>
#include <map>

#include "ast/ast.h"
#include "ast/NodeVisitor.h"


class ExecutionNodeVisitor : public NodeVisitor {
public:
    void Visit(ConstExpression&) override;
    void Visit(VariableExpression&) override;
    void Visit(BinaryExpression&) override;

    void Visit(AssignStatement&) override;
    void Visit(ComposeStatement&) override;

    int GetResByName(std::string name);
private:
    std::vector<int> stack_;
    std::map<std::string, int> variables_table_;
};