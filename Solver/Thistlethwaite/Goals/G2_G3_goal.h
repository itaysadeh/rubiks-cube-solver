#pragma once

#include "../../Goal.h"

struct G2_G3_Goal : public Goal
{
	G2_G3_Goal()
		: Goal({
			Rubiks::EMOVE::L , Rubiks::EMOVE::Lp , Rubiks::EMOVE::L2,
			Rubiks::EMOVE::R , Rubiks::EMOVE::Rp , Rubiks::EMOVE::R2,
			Rubiks::EMOVE::F2,
			Rubiks::EMOVE::B2,
			Rubiks::EMOVE::U2,
			Rubiks::EMOVE::D2
		},
			15, "G2 to G3")
	{
	}

	// G3 is contented when all of the colours on each face are either correct or opposite colour
	bool contented(const Rubiks& cube) const override;
};