#ifndef G0_G1_GOAL_H
#define G0_G1_GOAL_H

#include "../../goal.h"

struct G0_G1_Goal : public Goal
{
	G0_G1_Goal()
        : Goal({
            Rubiks::EMOVE::L , Rubiks::EMOVE::Lp , Rubiks::EMOVE::L2,
            Rubiks::EMOVE::R , Rubiks::EMOVE::Rp , Rubiks::EMOVE::R2,
            Rubiks::EMOVE::F , Rubiks::EMOVE::Fp , Rubiks::EMOVE::F2,
            Rubiks::EMOVE::B , Rubiks::EMOVE::Bp , Rubiks::EMOVE::B2,
            Rubiks::EMOVE::U , Rubiks::EMOVE::Up , Rubiks::EMOVE::U2,
            Rubiks::EMOVE::D , Rubiks::EMOVE::Dp , Rubiks::EMOVE::D2, })
	{
	}

	// G1 is contented when all the edges are oriented correctly
	bool contented(const Rubiks& cube) const override;
};

#endif // G0_G1_GOAL_H
