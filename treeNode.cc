#include "treeNode.h"
#include <iostream>

TreeNode::TreeNode(std::string cntt) : content{cntt} {}

std::string TreeNode::getContent()
{
    // your code starts here
    return this->content;
}

TreeNode *TreeNode::getLeftChild() const
{
    // your code starts here
    return this->leftChild;
}
TreeNode *TreeNode::getRightChild() const
{
    // your code starts here
    return this->rightChild;
}

void TreeNode::updateLeftChild(TreeNode *lChild)
{
    // your code starts here
    this->leftChild = lChild;
}

void TreeNode::updateChildren(TreeNode *lChild, TreeNode *rChild)
{
    // your code starts here
    this->leftChild = lChild;
    this->rightChild = rChild;
}
OperatorNode::OperatorNode(std::string cntt) : TreeNode{cntt} {}

// bool OperatorNode::evaluate(const std::map<std::string, bool> &assignment) const {
//     std::string root= this->getContent();
//     bool left_child = getLeftChild()->evaluate(assignment);
//     bool right_child = getRightChild() == nullptr ? false : getRightChild()->evaluate(assignment);
//     if(root=="+"){
//         return left_child||right_child;
//     }
//     if(root=="*"){
//         return left_child&&right_child;
//     }
//     if(root=="-"){
//         return !left_child;
//     }
//     return false;
// }

ConstantNode::ConstantNode(std::string cntt) : TreeNode{cntt} {}

// bool ConstantNode::evaluate(const std::map<std::string, bool> &assignment) const {
//     // your code starts here
//     if (this->getContent() == "0") {
//         return false;
//     }
//     return true;
// }

VariableNode::VariableNode(std::string cntt) : TreeNode{cntt} {}

// bool VariableNode::evaluate(const std::map<std::string, bool> &assignment) const {

//     if(assignment.find(this->getContent())!=assignment.end()){
//         return assignment.at(this->getContent());
//     }
//     throw "Error: incomplete assignment";
// }
TreeNode::~TreeNode()
{
    // your code starts here
}
