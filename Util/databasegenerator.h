#ifndef DATABASE_GENERATOR_H
#define DATABASE_GENERATOR_H
#include <string>
#include <iostream>

#include "../Solver/database.h"
#include "../Solver/goal.h"

#include "../Util/timer.h"
#include "../Util/searchutil.h"

// searches the cube (IDDFS) for all possible states and stores the depth of each state in a file
class DatabaseGenerator
{
public:
    // if a cube isn't passed the database will be generated using a solved cube
    void generate(const Goal& goal, Database& database, const Rubiks& pBaseCube = Rubiks());

private:
    bool databaseSearcher(Rubiks cube, Rubiks::EMOVE lastMove, const Goal& goal, Database& database, uint8_t depth, uint8_t maxDepth, std::vector<uint8_t>& lastIterationVisit) const;

    SearchUtil searchUtil;
};

#endif // DATABASE_GENERATOR_H
