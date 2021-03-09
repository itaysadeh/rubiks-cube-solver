#include "Thistlethwaite.h"

Thistlethwaite::Thistlethwaite()
{
    m_G0G1.useDatabase = true;
    m_G1G2.useDatabase = true;
    m_G2G3.useDatabase = true;

    m_groups = {
        &m_G0G1,
        &m_G1G2,
        &m_G2G3,
        &m_G3G4
    };
    
    for (auto group : m_groups)
    {
        if (group->useDatabase)
        {
            // loads database, or generates it if a file is not provided
            group->loadDatabase();
        }
    }
}

std::vector<Rubiks::EMOVE> Thistlethwaite::solve(const Rubiks& cube) const
{
    Timer              timer;
    Rubiks             currCubeState = cube;
    std::vector<EMOVE> result;
    double             timeToSolve = 0;

    for (const auto& group : m_groups)
    {
        timer.set();

        std::cout << "Solving " << group->goal->name << " :\n";
        // partial group solution
        std::vector<EMOVE> groupResult;
        groupResult.reserve(group->goal->maxDepth);

        groupResult = (group->useDatabase) ?
            Astar(currCubeState, *group->goal, *group->database) :
            IDDFS(currCubeState, *group->goal, *group->database);

        // add partial solution to the end result
        result.insert(result.end(), groupResult.begin(), groupResult.end());
        // perform the partial group solution to pass the new state to the next group
        for (const auto& move : groupResult)
        {
            currCubeState.performMove(move);
        }

        double groupSolveTime = timer.get();

        std::string currentName = group->goal->name;
        size_t      movesAmount = groupResult.size();
        std::cout << "Elapsed time: (" << groupSolveTime << "ms), Moves: (" << movesAmount << ")\n";

        timeToSolve += groupSolveTime;
    }

    // print solving statistics
    std::cout << "Total Time to solve: " << (int)(timeToSolve / 1000) << " seconds. (" << timeToSolve << "ms)\n";
    std::cout << "Moves(" << result.size() << "): ";
    for (const auto& move : result)
    {
        std::cout << cube.getMoveName(move);
    }
    std::cout << "\n";

    return result;
}
