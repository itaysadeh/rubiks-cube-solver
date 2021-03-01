#pragma once

#include "../../../Goal.h"

struct G1_G2_Goal : public Goal
{
	G1_G2_Goal()
		: Goal({
			Rubiks::EMOVE::L , Rubiks::EMOVE::Lp , Rubiks::EMOVE::L2,
			Rubiks::EMOVE::R , Rubiks::EMOVE::Rp , Rubiks::EMOVE::R2,
			Rubiks::EMOVE::F , Rubiks::EMOVE::Fp , Rubiks::EMOVE::F2,
			Rubiks::EMOVE::B , Rubiks::EMOVE::Bp , Rubiks::EMOVE::B2,
			Rubiks::EMOVE::U2,
			Rubiks::EMOVE::D2 
			},
			13, "G1 to G2")
	{
	}

	// G2 is contented when all the edges are oriented correctly,
	// and when the edges on the M slice belong in it (to remove the need of F / B moves)
	bool contented(const Rubiks& cube) const override;
};