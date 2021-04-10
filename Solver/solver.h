#ifndef SOLVER_H
#define SOLVER_H

#include <vector>

#include "../Util/timer.h"
#include "../Cube/cube.h"
#include "searcher.h"

// base class for solvers that ensures a solver will have the means to search for a solution and return the result
struct Solver
{
    virtual std::vector<Rubiks::EMOVE> solve(const Rubiks& cube) const = 0;

protected:
    Searcher m_searcher;
};

#endif // SOLVER_H
