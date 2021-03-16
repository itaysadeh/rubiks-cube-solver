#pragma once

#include "../../Goal.h"

struct G2_G3_Goal : public Goal
{
	G2_G3_Goal()
		: Goal({
			Rubiks::EMOVE::L , 
			Rubiks::EMOVE::Lp , 
			Rubiks::EMOVE::L2,
			Rubiks::EMOVE::R , 
			Rubiks::EMOVE::Rp , 
			Rubiks::EMOVE::R2,
			Rubiks::EMOVE::F2,
			Rubiks::EMOVE::B2,
			Rubiks::EMOVE::U2,
			Rubiks::EMOVE::D2
		},
			15, "G2 to G3")
	{
	}

	// G3 is contented when it's possible to solve all the corners and edges using only
	// 180-degree moves (half twists). this is possible when all corners are in their natural
    // orbits (arranged in 2 tetrads split in 4 pairs), all edges are in their home slice and
    // the parity is even
	bool contented(const Rubiks& cube) const override;
};
