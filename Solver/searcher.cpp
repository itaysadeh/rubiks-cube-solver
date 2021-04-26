#include "searcher.h"

std::vector<Rubiks::EMOVE> Astar::search(const Rubiks& cube, const Goal& goal, const Database& database) const
{
    // compares node scores for logarithmic insertions
    auto compareNodeScore = [](pNode_t lhs, pNode_t rhs)->bool {
        return lhs->score > rhs->score;
    };

    bool    solved     = false;
    uint8_t rootScore  = database[cube];

    pNode_t rootNode   = std::make_shared<Node_Astar>(Node_Astar{ cube, nullptr, EMOVE::NO_MOVE, rootScore });
    pNode_t currNode   = nullptr;
    pNode_t solvedNode = nullptr;

    std::priority_queue<pNode_t, std::vector<pNode_t>, decltype(compareNodeScore)> Q;

    Q.push(rootNode);

    while (!Q.empty())
    {
        currNode = Q.top();
        Q.pop();

        // found a solution
        if (goal.contented(currNode->cube))
        {
            solvedNode = currNode;
            solved     = true;
            break;
        }
        // solved state in the database didn't satisfiy the goal
        if (database[currNode->cube] == 0)
        {
            throw std::logic_error("Searcher::Astar A solved state in the database didn't satisfiy the goal");
        }

        // generate child nodes
        for (const auto& move : goal.legalMoves)
        {
            if (searchUtil.isRedundant(move, currNode->move)) continue;
            
            Rubiks copy = currNode->cube;
            copy.performMove(move);

            uint32_t newIndex = database.getInd(copy);
            uint8_t  newScore = database[newIndex];

            // don't consider nodes that move away from a solution
            if (newScore < currNode->score)
            {
                pNode_t newNode = std::make_shared<Node_Astar>(Node_Astar{ copy, currNode, move, newScore });
                Q.push(newNode);
            }
            copy.revertMove(move);
        }
    }

    // no solution was found and the queue is empty, invalid database led to wrong assumptions
    if (!solved)
    {
        throw std::logic_error("Searcher::Astar Didn't find a solution, invalid database.");
    }

    std::vector<EMOVE> result;
    while (solvedNode->parent)
    {
        result.push_back(solvedNode->move);
        solvedNode = solvedNode->parent;
    }
    // moves are pushed in reverse order
    std::reverse(result.begin(), result.end());

    return result;
}

std::vector<Rubiks::EMOVE> IDDFS::search(const Rubiks& cube, const Goal& goal, const Database& database) const
{
    std::vector<EMOVE> result;

    uint8_t depth  = 0;
    bool    solved = false;

    Node_IDDFS rootNode = Node_IDDFS{ cube, EMOVE::NO_MOVE, 0 };

    while (!solved)
    {
        if (IDDFS_searcher(rootNode, goal, depth, result))
        {
            solved = true;
        }
        depth++;
    }
    // moves are pushed in reverse order
    std::reverse(result.begin(), result.end());

    return result;
}

bool IDDFS::IDDFS_searcher(Node_IDDFS node, const Goal& goal, uint8_t maxDepth, std::vector<EMOVE>& result) const
{
    // IDDFS looks at nodes multiple times, only checks for solutions at leaf level
    if (node.depth == maxDepth) return goal.contented(node.cube);

    for (const auto move : goal.legalMoves)
    {
        if (searchUtil.isRedundant(move, node.move)) continue;

        node.cube.performMove(move);
        uint8_t currDepth = node.depth + 1;

        if (IDDFS_searcher(Node_IDDFS{node.cube, move, currDepth}, goal, maxDepth, result))
        {
            // solution found, moves pushed to result
            result.push_back(move);
            return true;
        }
        node.cube.revertMove(move);
    }

    // branch lead to a dead end
    return false;
}
