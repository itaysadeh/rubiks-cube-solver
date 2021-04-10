#ifndef G1_G2_GOAL_H
#define G1_G2_GOAL_H

#include "../../goal.h"

struct G1_G2_Goal : public Goal
{
	G1_G2_Goal()
        : Goal({
            Rubiks::EMOVE::L , Rubiks::EMOVE::Lp , Rubiks::EMOVE::L2,
			Rubiks::EMOVE::R , Rubiks::EMOVE::Rp , Rubiks::EMOVE::R2,
			Rubiks::EMOVE::F , Rubiks::EMOVE::Fp , Rubiks::EMOVE::F2,
			Rubiks::EMOVE::B , Rubiks::EMOVE::Bp , Rubiks::EMOVE::B2,
			Rubiks::EMOVE::U2,
            Rubiks::EMOVE::D2, })
	{
	}

	// G2 is contented when all the corners are oriented correctly and the M-slice
	// edges are brought back intro their slice
	bool contented(const Rubiks& cube) const override;
};

#endif // G1_G2_GOAL_H
