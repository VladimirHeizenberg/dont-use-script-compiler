#pragma once

#include <vector>
#include <map>

#include "ast/ast.h"
#include "ast/NodeVisitor.h"


class ExecutionNodeVisitor : public NodeVisitor {
public:
    void visit(ConstExpression&) override;
    void visit(BinaryExpression&) override;

    void visit(AssignStatement&) override;

    int GetResByName(std::string name);
private:
    std::vector<int> stack_;
    std::map<std::string, int> variables_table_;
};