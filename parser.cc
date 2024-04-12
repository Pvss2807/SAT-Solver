#include "parser.h"
#include "treeNode.h"
#include "tokenizer.h"
#include <iostream>

FormulaParser::FormulaParser(std::string ln) : tknzr{new Tokenizer{ln, true}}
{
}

TreeNode *FormulaParser::parseFormula()
{
    // your code starts here
    TreeNode *left_plus = parseConjTerm();
    TreeNode *plusNode;
    if (tknzr->getToken().content == "+")
    {
        plusNode = new OperatorNode("+");
        tknzr->advanceToken();
        TreeNode *right_plus = parseFormula();
        plusNode->updateChildren(left_plus, right_plus);
        return plusNode;
    }
    
    return left_plus;
}

TreeNode *FormulaParser::parseConjTerm()
{
    // your code starts here
    TreeNode *star_left = parseTerm();
    TreeNode *starNode;
    if (tknzr->hasToken() && tknzr->getToken().content == "*")
    {
        starNode = new OperatorNode("*");
        tknzr->advanceToken();
        TreeNode *star_right = parseConjTerm();
        starNode->updateChildren(star_left, star_right);
        return starNode;
    }
    return star_left;
}
TreeNode *FormulaParser::parseTerm()
{
    // your code starts here
    TreeNode *t;
    if (tknzr->getToken().type == "constant")
    {
        t = new ConstantNode(tknzr->getToken().content);
        tknzr->advanceToken();
        if(tknzr->getToken().type == "variable" || tknzr->getToken().type == "constant"
         || tknzr->getToken().content == "(" || tknzr->getToken().content == "-")
        {
            throw "Error: invalid input";
        }
        return t;
    }
    else if (tknzr->getToken().type == "variable")
    {
        t = new VariableNode(tknzr->getToken().content);
        tknzr->advanceToken();
        if(tknzr->getToken().type == "variable" || tknzr->getToken().type == "constant"
         || tknzr->getToken().content == "-" || tknzr->getToken().content == "(")
        {
            throw "Error: invalid input";
        }
        return t; 
    }
    else if (tknzr->getToken().content == "-")
    {
        t = new OperatorNode("-");
        tknzr->advanceToken();
        if(tknzr->getToken().content == ")" || tknzr->getToken().content == "*" || tknzr->getToken().content == "+")
            {
                throw "Error: invalid input";
            }
        TreeNode *t1 = parseTerm();
        t->updateLeftChild(t1);
        return t;  
    }
    else if (tknzr->getToken().content == "(")
    {
        tknzr->advanceToken();
        t = parseFormula();
        if (tknzr->hasToken() && tknzr->getToken().content == ")")
        {
            tknzr->advanceToken();
            if(tknzr->getToken().content=="(" || tknzr->getToken().type=="variable"||tknzr->getToken().type=="constant"){
            throw "Error: invalid input";
        }
        return t;
        }
        else{
            throw "Error: invalid input";
        }        
    }
    else{
        throw "Error: invalid input";
    }
    
}

TreeNode *FormulaParser::getTreeRoot()
{
    return parseFormula();
}

FormulaParser::~FormulaParser()
{
    
    delete tknzr;
}

// AssignmentParser::AssignmentParser(std::string ln) : tknzr{new Tokenizer{ln, false}}
// {
// }
// std::map<std::string, bool> AssignmentParser::parseAssignment()
// {
//     std::map<std::string, bool> results;
    
//     bool flag;
//     std::string key;
//     int b;
//     while (tknzr->hasToken())
//     {
//         if (tknzr->getToken().type == "variable")
//         {
//             key = tknzr->getToken().content;
//             if (results.find(key) != results.end())
//             {
//                 tknzr->advanceToken();
//                 std::string value = (tknzr->getToken().content);
//                 bool temp;
//                 if (value == "0")
//                     temp = false;
//                 else
//                     temp = true;
//                 if (results.at(key) == temp)
//                 {
//                     continue;
//                 }
//                 else
//                 {
//                     throw "Error: contradicting assignment";
//                 }
//             }
//         }
//         if (tknzr->getToken().type == "constant" && tknzr->getToken().content == "0")
//         {
//             b = false;
//             results.insert({key, b});
//         }
//         if (tknzr->getToken().type == "constant" && tknzr->getToken().content == "1")
//         {
//             b = true;
//             results.insert({key, b});
//         }
//         tknzr->advanceToken();
//     }
//     return results;
// }

// AssignmentParser::~AssignmentParser()
// {
//     delete tknzr;
// }
