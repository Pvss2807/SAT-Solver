#include "tseitinTransformer.h"
#include "treeNode.h"
#include <cctype>
#include <iostream>

TseitinTransformer::TseitinTransformer(TreeNode *root) : formulaRoot{root} {}

int TseitinTransformer::transSubformula(TreeNode *subRoot)
{
  // your code starts here
  if (subRoot->getContent() == "+" || subRoot->getContent() == "-" || subRoot->getContent() == "*")
  {
    this->varIdCounter++;
    int left;
    int right;
    int operatoriD = this->varIdCounter;
    if (subRoot->getContent() == "-")
    {

      left = this->transSubformula(subRoot->getLeftChild());
      addNegEq(operatoriD, left);
      return operatoriD;
    }
    if (subRoot->getContent() == "+")
    {
      if (subRoot->getLeftChild() != nullptr)
      {
        left = this->transSubformula(subRoot->getLeftChild());
      }
      if (subRoot->getRightChild() != nullptr)
      {
        right = this->transSubformula(subRoot->getRightChild());
      }
      addOrEq(operatoriD, left, right);
      return operatoriD;
    }
    if (subRoot->getContent() == "*")
    {
      if (subRoot->getLeftChild() != nullptr)
      {
        left = this->transSubformula(subRoot->getLeftChild());
      }
      if (subRoot->getRightChild() != nullptr)
      {
        right = this->transSubformula(subRoot->getRightChild());
      }
      addAndEq(operatoriD, left, right);
      return operatoriD;
    }
  }
  else
  {
    if (this->varIdTable.find(subRoot->getContent()) != this->varIdTable.end())
    {
      return this->varIdTable[subRoot->getContent()];
    }
    else
    {
      this->varIdCounter++;
      this->varIdTable[subRoot->getContent()] = this->varIdCounter;
      return this->varIdTable[subRoot->getContent()];
    }
  }
}
TreeNode *TseitinTransformer::getTreeRoot()
{
  return this->formulaRoot;
}
void TseitinTransformer::addNegEq(int curID, int childID)
{
  // your code starts here
  std::vector<int> negVector;
  negVector.push_back(-1 * curID);
  negVector.push_back(-1 * childID);
  this->cnf.push_back(negVector);
  while (!negVector.empty())
  {
    negVector.pop_back();
  }
  negVector.push_back(curID);
  negVector.push_back(childID);
  this->cnf.push_back(negVector);
}

void TseitinTransformer::addOrEq(int curID, int leftID, int rightID)
{
  // your code starts here
  std::vector<int> orVector;
  orVector.push_back(-1 * curID);
  orVector.push_back(leftID);
  orVector.push_back(rightID);
  this->cnf.push_back(orVector);
  while (!orVector.empty())
  {
    orVector.pop_back();
  }
  orVector.push_back(-1 * leftID);
  orVector.push_back(curID);
  this->cnf.push_back(orVector);
  while (!orVector.empty())
  {
    orVector.pop_back();
  }
  orVector.push_back(curID);
  orVector.push_back(-1 * rightID);
  this->cnf.push_back(orVector);
}

void TseitinTransformer::addAndEq(int curID, int leftID, int rightID)
{
  // your code starts here
  std::vector<int> andVector;
  andVector.push_back(curID);
  andVector.push_back(-1 * leftID);
  andVector.push_back(-1 * rightID);
  this->cnf.push_back(andVector);
  while (!andVector.empty())
  {
    andVector.pop_back();
  }
  andVector.push_back(leftID);
  andVector.push_back(-1 * curID);
  this->cnf.push_back(andVector);
  while (!andVector.empty())
  {
    andVector.pop_back();
  }
  andVector.push_back(-1 * curID);
  andVector.push_back(rightID);
  this->cnf.push_back(andVector);
}

std::vector<std::vector<int>> TseitinTransformer::transform()
{
  // your code starts here
  int root = this->transSubformula(getTreeRoot());
  this->cnf.push_back({1});
  return this->cnf;
}

std::string TseitinTransformer::cnfString() const
{
  std::string result = "";
  // your code starts here

  return result;
}

unsigned int TseitinTransformer::getVarNum() const
{
  // your code starts here
  return this->varIdCounter;
}
