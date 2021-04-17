#include "thistlethwaite.h"

Thistlethwaite::Thistlethwaite()
{
    // init groups
    m_G0G1.useDatabase = true;
    m_G1G2.useDatabase = true;
    m_G2G3.useDatabase = true;
    m_G3G4.useDatabase = true;

    m_G0G1.name = "G0->G1";
    m_G1G2.name = "G1->G2";
    m_G2G3.name = "G2->G3";
    m_G3G4.name = "G3->G4";

    m_groups = {
        &m_G0G1,
        &m_G1G2,
        &m_G2G3,
        &m_G3G4
    };
    
    for (auto& group : m_groups)
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

    std::cout << "Thistlethwaite's algorithm:" << std::endl;

    for (const auto& group : m_groups)
    {
        timer.set();

        std::cout << group->name << ": ";

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

        std::cout << "Elapsed time: " << groupSolveTime << "ms, ";
        std::cout << "Moves: " << groupResult.size() << std::endl;
        combinedSolveTime += groupSolveTime;
    }

    // overall solve statistics
    std::cout << std::endl;
    std::cout << "Solved in: " << (int)combinedSolveTime / 1000 << " seconds " << "(" << combinedSolveTime << "ms)." << std::endl;
    std::cout << "Moves(" << result.size() << "): ";
    for (const auto& move : result)
    {
        std::cout << cube.getMoveName(move);
    }
    std::cout << std::endl;

    return result;
}
