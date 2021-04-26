#ifndef SEARCHER_H
#define SEARCHER_H

#include <vector>
#include <memory>
#include <algorithm>
#include <queue>

#include "../Util/searchutil.h"
#include "../Cube/cube.h"
#include "database.h"
#include "goal.h"

struct Algorithm
{
    using EMOVE = Rubiks::EMOVE;
    virtual std::vector<Rubiks::EMOVE> search(const Rubiks& cube, const Goal& goal, const Database& database) const = 0;
protected:
    SearchUtil searchUtil;
};

// faster solutions, requires a database
struct Astar : public Algorithm
{
    struct Node_Astar;
    using pNode_t = std::shared_ptr<Node_Astar>;

    struct Node_Astar
    {
        Rubiks  cube;
        pNode_t parent = nullptr;
        EMOVE   move   = EMOVE::NO_MOVE;
        uint8_t score;
    };

    std::vector<EMOVE> search(const Rubiks& cube, const Goal& goal, const Database& database) const override;
};

// slower solutions, doesn't require a database
struct IDDFS : public Algorithm
{
    struct Node_IDDFS
    {
        Rubiks  cube;
        EMOVE   move;
        uint8_t depth;
    };

    std::vector<EMOVE> search(const Rubiks& cube, const Goal& goal, const Database& database) const override;
    bool IDDFS_searcher(Node_IDDFS node, const Goal& goal, uint8_t maxDepth, std::vector<EMOVE>& result) const;
};

// 

// contains all search algorithms
struct Searcher
{
    Astar astar;
    IDDFS iddfs;
};

#endif // SEARCHER_H
