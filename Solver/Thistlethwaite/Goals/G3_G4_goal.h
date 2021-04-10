#ifndef G3_G4_GOAL_H
#define G3_G4_GOAL_H

#include "../../goal.h"

struct G3_G4_Goal : public Goal
{
	G3_G4_Goal()
        : Goal({
			Rubiks::EMOVE::L2,
			Rubiks::EMOVE::R2,
			Rubiks::EMOVE::F2,
			Rubiks::EMOVE::B2,
			Rubiks::EMOVE::U2,
            Rubiks::EMOVE::D2, })
	{
	}

	// G4 is contented when the cube is solved
	bool contented(const Rubiks& cube) const override;
};

#endif // G3_G4_GOAL_H
