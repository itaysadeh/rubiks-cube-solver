#pragma once

#include <string>
#include <iostream>
//
#include <set>
//
#include "../Database/Database.h"
#include "../Solver/Goal.h"

#include "../Util/Timer.h"
#include "../Util/MovesSimplifier.h"

// IDDFS is used to search for all possible cube states reachable from a solved state
// and assign each state the distance from the root position
class DatabaseGenerator
{
public:
    // if a cube isn't passed, database will be generated using a solved cube
    void generate(const Goal& goal, Database& database, const Rubiks& pBaseCube = Rubiks());

private:
    bool databaseSearcher(Rubiks cube, Rubiks::EMOVE lastMove, const Goal& goal, Database& database, uint8_t depth, uint8_t maxDepth) const;

    MovesSimplifier m_movesSimplifier;
};
