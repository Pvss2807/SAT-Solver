#include "tseitinTransformer.h"
#include "satSolver.h"
#include "treeNode.h"
#include "parser.h"
#include <iostream>
// The program shall continuously ask for new inputs from standard input and output to the standard output
// The program should terminate gracefully (and quietly) once it sees EOF
int main()
{
  std::string line;
  while (getline(std::cin, line)) // continuously asking for new inputs from standard input
  {
    // store each input line

    // your code starts here
    try
    {
      std::string formulaStr = line; // store the formula string
      TreeNode *t;
      FormulaParser *formulaParser = new FormulaParser(formulaStr);
      t = formulaParser->getTreeRoot();
      TseitinTransformer *tseitinTransformer = new TseitinTransformer(t);
      std::vector<std::vector<int>> res = tseitinTransformer->transform();
      // std::cout << "This is tseitin" << std::endl;
      // for (int i = 0; i < res.size(); i++)
      // {
      //   for (int j = 0; j < res[i].size(); j++)
      //   {
      //     std::cout << res[i][j] << std::endl;
      //   }
      //   std::cout << "This is clause end" << std::endl;
      // }
      bool result = satCallingMiniSat(tseitinTransformer->getVarNum(), res);
      if (result)
      {
        std::cout << "sat" << std::endl;
      }
      else
      {
        std::cout << "unsat" << std::endl;
      }
    }
    catch (const char *error)
    {
      std::cout << error << std::endl;
    }
  }
}
