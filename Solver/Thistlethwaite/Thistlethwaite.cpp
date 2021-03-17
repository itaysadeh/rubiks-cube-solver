#include "Thistlethwaite.h"

Thistlethwaite::Thistlethwaite()
{
    m_G0G1.useDatabase = true;
    m_G1G2.useDatabase = true;
    m_G2G3.useDatabase = true;
    m_G3G4.useDatabase = false;

    m_G0G1.name = "G0G1";
    m_G1G2.name = "G1G2";
    m_G2G3.name = "G2G3";
    m_G3G4.name = "G3G4";

    m_groups = {
        &m_G0G1,
        &m_G1G2,
        &m_G2G3,
        &m_G3G4
    };
    
    for (Group* group : m_groups)
    {
        if (group->useDatabase)
        {
            group->loadDatabase();
        }
    }
}

std::vector<Rubiks::EMOVE> Thistlethwaite::solve(const Rubiks& cube) const
{
    Timer              timer;
    Rubiks             cubeState = cube;
    std::vector<EMOVE> result;
    double             combinedSolveTime = 0;

    for (Group* group : m_groups)
    {
        timer.set();

        std::cout << "Solving " << group->name << " :\n";

        // partial group solution
        std::vector<EMOVE> groupResult;
        groupResult = (group->useDatabase) ?
            m_searcher.astar.search(cubeState, *group->goal, *group->database) :
            m_searcher.iddfs.search(cubeState, *group->goal, *group->database);

        // add partial solution to the end result
        result.insert(result.end(), groupResult.begin(), groupResult.end());
        // perform the partial group solution to pass the new state to the next group
        for (const EMOVE move : groupResult)
        {
            cubeState.performMove(move);
        }

        // group solve statistics
        double groupSolveTime = timer.get();

        std::cout << "Elapsed time: (" << groupSolveTime << "ms)" << "\n";
        std::cout << "Moves: (" << groupResult.size() << ")\n";
        combinedSolveTime += groupSolveTime;
    }

    // solve statistics
    std::cout << "Solved in: (" << (float)combinedSolveTime << "ms)\n";
    std::cout << "Moves(" << result.size() << "): ";
    for (const EMOVE move : result)
    {
        std::cout << cube.getMoveName(move);
    }
    std::cout << "\n";

    return result;
}
