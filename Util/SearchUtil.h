#ifndef SEARCH_UTIL_H
#define SEARCH_UTIL_H

#include "../Cube.h"

// speeds searches by pruning redundant moves (moves that lead to identical states) from a search tree
struct SearchUtil
{
    using EMOVE = Rubiks::EMOVE;

    // retruns whether a move should be considered based on the last move
    bool isRedundant(EMOVE curr, EMOVE last) const;
};

#endif // SEARCH_UTIL_H
