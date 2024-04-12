#include "satSolver.h"
#include "minisat/core/SolverTypes.h"
#include "minisat/core/Solver.h"
#include <memory>
#include <iostream>
#include <vector>

bool satCallingMiniSat(unsigned int numVar, std::vector<std::vector<int>> &cnf)
{
  // your code starts here
  std::unique_ptr<Minisat::Solver> solver(new Minisat::Solver());
  // Minisat::vec<Minisat::Lit> literal_vector;
  Minisat::vec<Minisat::Lit> literal_vector;
  Minisat::vec<Minisat::Lit> cluaseargs;

  Minisat::Lit l1, l2, l3, l4;
  for (int i = 0; i < numVar; i++)
  {
    l1 = Minisat::mkLit(solver->newVar());
    literal_vector.push(l1);
  }
  for (int j = 0; j < cnf.size(); j++)
  {

    for (int k = 0; k < cnf[j].size(); k++)
    {
      l1 = literal_vector[abs(cnf[j][k]) - 1];
      if (cnf[j][k] < 0)
      {
        cluaseargs.push(~l1);
      }
      else
      {
        cluaseargs.push(l1);
      }
    }
    solver->addClause(cluaseargs);
    cluaseargs.clear();
  }

  bool res = solver->solve();

  solver.reset(new Minisat::Solver());

  // at this point the solver is ready. You must create new
  // variable and new clauses

  return res;
}
