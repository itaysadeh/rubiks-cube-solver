#include "Thistlethwaite.h"

Thistlethwaite::Thistlethwaite()
{
    // TEMPORARY
    m_G0G1.useDatabase = true;
    m_G1G2.useDatabase = true;
    //
}

std::vector<Rubiks::EMOVE> Thistlethwaite::solve(const Rubiks& cube)
{
    Timer               timer;
    Rubiks              copy = cube;
    std::vector<EMOVE>  result;
    double              timeToSolve = 0;

    std::vector<Group*> groups = {
        &m_G0G1,
        &m_G1G2,
        &m_G2G3,
        &m_G3G4
    };

    std::cout << "Sovling using Thistlethwaite's algorithm: \n";

    for (const auto& group : groups)
    {
        std::cout << "Solving " << group->goal->name << " :\n";
        // partial group solution
        std::vector<EMOVE> groupResult;
        groupResult.reserve(group->goal->maxDepth);

        timer.set();
        groupResult = (group->useDatabase) ? // TEMPORARY
            Astar(copy, *group->goal, *group->database) :
            IDDFS(copy, *group->goal, *group->database);

        // insert partial solution in the end of the final solution
        result.insert(result.end(), groupResult.begin(), groupResult.end());
        // perform the partial solution on a copy and pass it to the next group
        for (const auto& move : groupResult)
        {
            copy.performMove(move);
        }

        double groupSolveTime = timer.get();

        std::string currentName = group->goal->name;
        size_t      movesAmount = groupResult.size();
        std::cout << "Elapsed time: (" << groupSolveTime << "ms), Moves: (" << movesAmount << ")\n";

        timeToSolve += groupSolveTime;
    }

    std::cout << "Total Time to solve: " << (int)(timeToSolve / 1000) << " seconds.\n";

    return result;
}
