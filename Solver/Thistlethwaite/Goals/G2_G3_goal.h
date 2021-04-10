#ifndef G2_G3_GOAL_H
#define G2_G3_GOAL_H

#include "../../goal.h"

struct G2_G3_Goal : public Goal
{
	G2_G3_Goal()
        : Goal({
			Rubiks::EMOVE::L , Rubiks::EMOVE::Lp , Rubiks::EMOVE::L2,
			Rubiks::EMOVE::R , Rubiks::EMOVE::Rp , Rubiks::EMOVE::R2,
			Rubiks::EMOVE::F2,
			Rubiks::EMOVE::B2,
			Rubiks::EMOVE::U2,
            Rubiks::EMOVE::D2, })
	{
	}

    // G3 is contented when it's possible to solve the cube without 90 degree twists
    // to ensure that, all edges and corners are in their orbits and the parity is even

    // this implementation splits the corners into 4 pairs instead of forming 2 tetrads
	bool contented(const Rubiks& cube) const override;
};

#endif // G2_G3_GOAL_H
