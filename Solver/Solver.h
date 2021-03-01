#pragma once

#include <vector>
#include <array>
#include <memory>
#include <algorithm>
#include <queue>
#include <unordered_map>
#include <stack>
#include <math.h>
#include <queue>

#include "../Util/Timer.h"
#include "../Util/PermutationIndexer.h"
#include "../Util/MovesSimplifier.h"
#include "../Cube.h"

#include "../Database/Database.h"
#include "Goal.h"

// abstract class for all solvers
struct Solver
{
    // this will only be avaliable in classes that inherit from Solver, and not in the global scope
    using EMOVE = Rubiks::EMOVE;

    //virtual std::vector<Rubiks::EMOVE> solve(const Rubiks& cube) = 0;

//protected:
    // search algorithms:
        // A*       when using a database
    std::vector<EMOVE> Astar(const Rubiks& cube, const Goal& goal, const Database& database) const;
        // IDDFS    when not using a database
    std::vector<Rubiks::EMOVE> IDDFS(const Rubiks& cube, const Goal& goal, const Database& database) const;
    bool searcher(Rubiks cube, Rubiks::EMOVE lastMove, const Goal& goal, const Database& database,
        uint8_t depth, uint8_t maxDepth, std::vector<Rubiks::EMOVE>& result) const;

    // TODO: move this to the utility class
    std::vector<EMOVE> removeRedundantMoves(std::vector<Rubiks::EMOVE>& moves) const;
private:
    std::vector<Rubiks::EMOVE> m_moves;
    Rubiks m_cube;
    MovesSimplifier m_movesSimplifier;
};