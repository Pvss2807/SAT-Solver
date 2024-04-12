#ifndef TNODE_H
#define TNODE_H

#include <string>
#include <map>

// abstract superclass of the syntax tree node
class TreeNode
{
    std::string content;
    TreeNode *leftChild = nullptr;
    TreeNode *rightChild = nullptr;

public:
    TreeNode *getLeftChild() const;
    TreeNode *getRightChild() const;

public:
    TreeNode(std::string cntt);
    std::string getContent();
    // virtual bool evaluate(const std::map<std::string, bool> &assignment) const = 0; // pure virtual method
    void updateLeftChild(TreeNode *lChild);
    void updateChildren(TreeNode *lChild, TreeNode *rChild);
    virtual ~TreeNode();
};

// concrete tree node of opertaor type
class OperatorNode : public TreeNode
{
public:
    OperatorNode(std::string cntt);
    // bool evaluate(const std::map<std::string, bool> &assignment) const override;
};

// concrete tree node of constant type
class ConstantNode : public TreeNode
{
public:
    ConstantNode(std::string cntt);
    // bool evaluate(const std::map<std::string, bool> &assignment) const override;
};

// concrete tree node of varibale type
class VariableNode : public TreeNode
{
    std::map<std::string, int> tree_assignment;

public:
    VariableNode(std::string cntt);
    // bool evaluate(const std::map<std::string, bool> &assignment) const override;
};
#endif
