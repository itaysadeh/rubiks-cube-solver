#include "databasegenerator.h"

void DatabaseGenerator::generate(const Goal& goal, Database& database, const Rubiks& baseCube) const
{
    Rubiks  cube  = baseCube;
    uint8_t depth = 0;
    Timer   timer;

    timer.set();

    while (!database.full())
    {
        // keeps track of visited nodes in each of the iterations
        std::vector<bool> visited(database.size(), false);

        std::cout << "Depth: " << (int)depth << ". ";
        if (databaseSearcher(cube, Rubiks::EMOVE::NO_MOVE, goal, database, 0, depth, visited))
        {
            break;
        }

        std::cout << "visited states: " << database.currentSize() << " / " << database.size() << std::endl;
        depth++;
    }

    // all states visited, write the result to a file
    database.write();
    std::cout << "Finished generating (" << timer.get() / 1000 << " seconds)" << std::endl;
}


bool DatabaseGenerator::databaseSearcher(Rubiks cube, Rubiks::EMOVE lastMove, const Goal& goal, Database& database, uint8_t depth, uint8_t maxDepth, std::vector<bool>& visited) const
{
    // index of the current cube state
    uint32_t index = database.getInd(cube);

    // prunes the branch if the current cube state was already visited in an earlier 
    // iteration, or in the same iteration by a different branch
    if (visited[index] || depth > database[index]) return false;
    
    // marks the current cube state as visited
    visited[index] = true;

    // index the cube states in the database in leaf level
    if (depth == maxDepth)
    {
        database.set(index, depth);
        return database.full();
    }
    else
    {
        // generate child nodes
        for (const auto move : goal.legalMoves)
        {
            if (searchUtil.isRedundant(move, lastMove)) continue;

            cube.performMove(move);

            if (databaseSearcher(cube, move, goal, database, depth + 1, maxDepth, visited))
            {
                return true;
            }

            cube.revertMove(move);
        }
    }

    // branch led to a dead end
    return false;
}
