#include "Solver.h"

std::vector<Rubiks::EMOVE> Solver::Astar(const Rubiks& cube, const Goal& goal, const Database& database) const
{
    using EMOVE = Rubiks::EMOVE;

    struct  Node;
    using   Node_S = std::shared_ptr<Node>;
    struct  Node
    {
        Node_S  parent;
        EMOVE   move;
        Rubiks  cube;
        uint8_t scoreG; // local distance (from root)
        uint8_t scoreH; // heuristic distance (from the database)
        uint8_t scoreF; // G + H
    };

    // for logarithmic insertion, the lowest F score is always looked at first in the queue
    auto compareNodeFScore = [](Node_S lhs, Node_S rhs)->bool {
        return lhs->scoreF > rhs->scoreF;
    };

    uint8_t rootScoreG = 0;
    uint8_t rootScoreH = database.getDistance(cube);
    uint8_t rootScoreF = rootScoreG + rootScoreH;

    Node_S rootNode     = std::make_shared<Node>(Node{nullptr, EMOVE::NO_MOVE, cube, rootScoreG, rootScoreH, rootScoreF});
    Node_S currNode  = nullptr;
    Node_S solvedNode   = nullptr;

    std::priority_queue<Node_S, std::vector<Node_S>, decltype(compareNodeFScore)> Q;
    Q.push(rootNode);

    while (!Q.empty())
    {
        // node wit the lowest F score
        currNode = Q.top();
        Q.pop();

        // break when a solution is found
        if (goal.contented(currNode->cube))
        {
            solvedNode = currNode;
            break;
        }

        if (database.getDistance(currNode->cube) == 0)
        {
            std::string a = (goal.contented(currNode->cube)) ? "Solved!" : "Not Solved!";
            std::cout << "[" << (int)database.getIndex(currNode->cube) << "] = 0; is " << a << "\n";
        }

        for (const EMOVE move : goal.legalMoves)
        {
            if (!m_movesSimplifier.isRedundant(move, currNode->move))
            {
                Rubiks copy = currNode->cube;
                copy.performMove(move);

                uint32_t newIndex  = database.getIndex(copy);
                uint8_t  newScoreG = currNode->scoreG + 1;
                uint8_t  newScoreH = database.getDistance(newIndex);
                uint8_t  newScoreF = newScoreG + newScoreH;

                // ignore nodes that move away from a solution
                if (newScoreF <= currNode->scoreF)
                {
                    Node_S newNode = std::make_shared<Node>(Node{currNode, move, copy, newScoreG, newScoreH, newScoreF});
                    Q.push(newNode);
                }
                copy.revertMove(move);
            }
        }
    }

    std::vector<EMOVE> result;

    // with a database a solution is guaranteed
    if (!solvedNode)
    {
        throw std::logic_error("Solver::Astar Didn't find a solution, invalid database");
    }

    while (solvedNode->parent)
    {
        result.push_back(solvedNode->move);
        solvedNode = solvedNode->parent;
    }
    // moves are pushed in reverse order
    std::reverse(result.begin(), result.end());

    return result;
}

std::vector<Rubiks::EMOVE> Solver::IDDFS(const Rubiks& cube, const Goal& goal, const Database& database) const
{
    using EMOVE = Rubiks::EMOVE;

    uint8_t depth = 0;
    std::vector<EMOVE> result;
    while (true)
    {
        if (searcher(cube, EMOVE::NO_MOVE, goal, database, 0, depth, result))
        {
            break;
        }
        depth++;
    }
    // moves are pushed in reverse order
    std::reverse(result.begin(), result.end());

    return result;
}

bool Solver::searcher(Rubiks cube, EMOVE lastMove , const Goal& goal, const Database& database,
    uint8_t depth, uint8_t maxDepth, std::vector<EMOVE>& result) const
{
    using EMOVE = Rubiks::EMOVE;
    // stop searching when max depth is reached, a solution might be closer in a different branch
    if (depth == maxDepth)
    {
        return false;
    }

    // goal reached
    if (goal.contented(cube))
    {
        return true;
    }

    for (const EMOVE move : goal.legalMoves)
    {
        if (!m_movesSimplifier.isRedundant(move, lastMove))
        {
            cube.performMove(move);

            // found a solution
            if (searcher(cube, move, goal, database, depth + 1, maxDepth, result))
            {
                // pushes moves in reverse order due to recursion
                result.push_back(move);
                return true;
            }
            cube.revertMove(move);
        }
    }

    // branch led to a dead end
    return false;
}

std::vector<Rubiks::EMOVE> Solver::removeRedundantMoves(std::vector<EMOVE>& moves) const
{
    return moves;
  /*  if (moves.size() < 2) return moves;

    std::vector<EMOVE> result;

    for (auto move : moves)
    {
        result.push_back(move);
    }

    for (std::size_t i = 0; i < moves.size(); ++i)
    {
        EMOVE prev = EMOVE::NO_MOVE;
        EMOVE insert = EMOVE::NO_MOVE;
        for (std::size_t j = 0; j < result.size(); ++j)
        {
            EMOVE curr = result[j];
            if (prev == EMOVE::U && curr == EMOVE::U || prev == EMOVE::Up && curr == EMOVE::Up)
            {
                insert = EMOVE::U2;
            }
            else if (prev == EMOVE::U2 && curr == EMOVE::U || prev == EMOVE::U && curr == EMOVE::U2)
            {
                insert = EMOVE::Up;
            }
            else if (prev == EMOVE::U2 && curr == EMOVE::Up || prev == EMOVE::Up && curr == EMOVE::U2)
            {
                insert = EMOVE::U;
            }
            else if (prev == EMOVE::L && curr == EMOVE::L || prev == EMOVE::Lp && curr == EMOVE::Lp)
            {
                insert = EMOVE::L2;
            }
            else if (prev == EMOVE::L2 && curr == EMOVE::L || prev == EMOVE::L && curr == EMOVE::L2)
            {
                insert = EMOVE::Lp;
            }
            else if (prev == EMOVE::L2 && curr == EMOVE::Lp || prev == EMOVE::Lp && curr == EMOVE::L2)
            {
                insert = EMOVE::L;
            }
            else if (prev == EMOVE::F && curr == EMOVE::F || prev == EMOVE::Fp && curr == EMOVE::Fp)
            {
                insert = EMOVE::F2;
            }
            else if (prev == EMOVE::F2 && curr == EMOVE::F || prev == EMOVE::F && curr == EMOVE::F2)
            {
                insert = EMOVE::Fp;
            }
            else if (prev == EMOVE::F2 && curr == EMOVE::Fp || prev == EMOVE::Fp && curr == EMOVE::F2)
            {
                insert = EMOVE::F;
            }
            else if (prev == EMOVE::R && curr == EMOVE::R || prev == EMOVE::Rp && curr == EMOVE::Rp)
            {
                insert = EMOVE::R2;
            }
            else if (prev == EMOVE::R2 && curr == EMOVE::R || prev == EMOVE::R && curr == EMOVE::R2)
            {
                insert = EMOVE::Rp;
            }
            else if (prev == EMOVE::R2 && curr == EMOVE::Rp || prev == EMOVE::Rp && curr == EMOVE::R2)
            {
                insert = EMOVE::R;
            }
            else if (prev == EMOVE::B && curr == EMOVE::B || prev == EMOVE::Bp && curr == EMOVE::Bp)
            {
                insert = EMOVE::B2;
            }
            else if (prev == EMOVE::B2 && curr == EMOVE::B || prev == EMOVE::B && curr == EMOVE::B2)
            {
                insert = EMOVE::Bp;
            }
            else if (prev == EMOVE::B2 && curr == EMOVE::Bp || prev == EMOVE::Bp && curr == EMOVE::B2)
            {
                insert = EMOVE::B;
            }
            else if (prev == EMOVE::D && curr == EMOVE::D || prev == EMOVE::Dp && curr == EMOVE::Dp)
            {
                insert = EMOVE::D2;
            }
            else if (prev == EMOVE::D2 && curr == EMOVE::R || prev == EMOVE::D && curr == EMOVE::D2)
            {
                insert = EMOVE::Dp;
            }
            else if (prev == EMOVE::D2 && curr == EMOVE::Dp || prev == EMOVE::Dp && curr == EMOVE::D2)
            {
                insert = EMOVE::D;
            }

            if (insert != EMOVE::NO_MOVE)
            {
               auto it = result.erase(result.begin() + j - 1);
               *it = insert;
               prev = *it;
               insert = EMOVE::NO_MOVE;
               break;
            }

            prev = result[j];
        }
    }*/

    //moves = result;
}
