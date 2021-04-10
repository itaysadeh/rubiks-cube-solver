#ifndef SEARCH_UTIL_H
#define SEARCH_UTIL_H

#include "../Cube/cube.h"

// helper functions for searching the cube or generating moves
struct SearchUtil
{
    using EMOVE = Rubiks::EMOVE;

    // checks if a sequence of moves is redundant
    bool isRedundant(EMOVE curr, EMOVE last) const;
};

#endif // SEARCH_UTIL_H
