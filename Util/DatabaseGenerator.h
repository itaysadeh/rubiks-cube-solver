#ifndef DATABASE_GENERATOR_H
#define DATABASE_GENERATOR_H
#include <string>
#include <iostream>

#include "../Solver/Database.h"
#include "../Solver/Goal.h"

#include "../Util/Timer.h"
#include "../Util/SearchUtil.h"

// IDDFS is used to search for all possible cube states reachable from a solved state
// and assign each state the distance from the root position
class DatabaseGenerator
{
public:
    // if a cube isn't passed, database will be generated using a solved cube
    void generate(const Goal& goal, Database& database, const Rubiks& pBaseCube = Rubiks());

private:
    bool databaseSearcher(Rubiks cube, Rubiks::EMOVE lastMove, const Goal& goal, Database& database, uint8_t depth, uint8_t maxDepth) const;

    SearchUtil searchUtil;
};

#endif // DATABASE_GENERATOR_H
