#pragma once

#include <string>
#include <vector>
#include <memory>

#include "../Cube.h"
#include "../Database/Database.h"

// base class for goals, provides:
// legalMoves = legal moves to reach the goal
// maxDepth   = maximum number of moves it takes to reach the goal
// name		  = name of the goal
// contented  = is the cube in a state that reached the goal

struct Goal
{
	Goal(const std::vector<Rubiks::EMOVE>& legal_moves, uint8_t max_depth, std::string&& name)
		: legalMoves(legal_moves), maxDepth(max_depth), name(name)
	{
	}

	virtual bool contented(const Rubiks& cube) const = 0;

	std::vector<Rubiks::EMOVE> legalMoves;
	uint8_t maxDepth;
	std::string name;
};


