#include "databasegenerator.h"

void DatabaseGenerator::generate(const Goal& goal, Database& database, const Rubiks& baseCube) const
{
    Rubiks  cube  = baseCube;
    uint8_t depth = 0;
    Timer   timer;

    timer.set();

    std::vector<uint8_t> lastIterationVisit(database.size(), (uint8_t)(-1));
    while (!database.full())
    {
        // keeps track of visited nodes in each of the iterations
        std::vector<bool> visited(database.size(), false);

        std::cout << "Depth: " << (int)depth << ". ";
<<<<<<< HEAD
        if (databaseSearcher(cube, Rubiks::EMOVE::NO_MOVE, goal, database, 0, depth, visited))
=======
        if (databaseSearcher(cube, Rubiks::EMOVE::NO_MOVE, goal, database, 0, depth, lastIterationVisit))
>>>>>>> 1b1df7ed78daeda9f3b8e95e1ed0b88634fd6785
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

<<<<<<< HEAD
bool DatabaseGenerator::databaseSearcher(Rubiks cube, Rubiks::EMOVE lastMove, const Goal& goal, Database& database, uint8_t depth, uint8_t maxDepth, std::vector<bool>& visited) const
=======
bool DatabaseGenerator::databaseSearcher(Rubiks cube, Rubiks::EMOVE lastMove, const Goal& goal, Database& database, uint8_t depth, uint8_t maxDepth, std::vector<uint8_t>& lastIterationVisit) const
>>>>>>> 1b1df7ed78daeda9f3b8e95e1ed0b88634fd6785
{
    // index of the current cube state
    uint32_t index = database.getInd(cube);

<<<<<<< HEAD
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
=======
    // prune a branch if a state has been visited at an earlier depth
    // or by a different branch during the same maxDepth iteration
    if (depth <= database[index] && lastIterationVisit[index] != maxDepth)
    {
        lastIterationVisit[index] = maxDepth;
        // IDDFS looks at nodes multiple times, so indexing should only
        // be done at leaf level since lower depths have already been visited
        if (depth == maxDepth)
        {
            database.set(index, depth);
        }
        else
>>>>>>> 1b1df7ed78daeda9f3b8e95e1ed0b88634fd6785
        {
            if (searchUtil.isRedundant(move, lastMove)) continue;

<<<<<<< HEAD
            cube.performMove(move);
=======
                    if (databaseSearcher(cube, move, goal, database, depth + 1, maxDepth, lastIterationVisit))
                    {
                        return true;
                    }
>>>>>>> 1b1df7ed78daeda9f3b8e95e1ed0b88634fd6785

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
