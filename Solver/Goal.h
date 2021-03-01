#pragma once

#include <string>
#include <vector>
#include <memory>

#include "../Cube.h"
#include "../Database/Database.h"

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


