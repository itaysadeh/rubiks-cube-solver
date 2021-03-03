#pragma once

#include "../../Goal.h"

struct G3_G4_Goal : public Goal
{
	G3_G4_Goal()
		: Goal({
			Rubiks::EMOVE::L2,
			Rubiks::EMOVE::R2,
			Rubiks::EMOVE::F2,
			Rubiks::EMOVE::B2,
			Rubiks::EMOVE::U2,
			Rubiks::EMOVE::D2
		},
			17, "G3 to G4")
	{
	}

	// G4 is contented when the cube is solved
	bool contented(const Rubiks& cube) const override;
};