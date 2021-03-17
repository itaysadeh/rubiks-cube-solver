#ifndef GOAL_H
#define GOAL_H

#include <vector>
#include <memory>

#include "../Cube.h"
#include "Database.h"

// base class for a goal that checks if a goal is reached and provides the moves to reach it
struct Goal
{
    Goal(const std::vector<Rubiks::EMOVE>& legal_moves)
        : legalMoves(legal_moves)
	{
	}

	virtual bool contented(const Rubiks& cube) const = 0;

	std::vector<Rubiks::EMOVE> legalMoves;
};

#endif // GOAL_H
