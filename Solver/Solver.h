#pragma once

#include <vector>
#include <array>
#include <memory>
#include <algorithm>
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
    using EMOVE = Rubiks::EMOVE;

    virtual std::vector<EMOVE> solve(const Rubiks& cube) const = 0;

protected:
    // search algorithms:
        // A*       when using a database
    std::vector<EMOVE> Astar(const Rubiks& cube, const Goal& goal, const Database& database) const;
        // IDDFS    when not using a database
    std::vector<EMOVE> IDDFS(const Rubiks& cube, const Goal& goal, const Database& database) const;
    bool searcher(Rubiks cube, EMOVE lastMove, const Goal& goal, const Database& database,
                    uint8_t depth, uint8_t maxDepth, std::vector<EMOVE>& result) const;

    // TODO: move this to the utility class
    std::vector<EMOVE> removeRedundantMoves(std::vector<EMOVE>& moves) const;

private:
    MovesSimplifier m_movesSimplifier;
};
