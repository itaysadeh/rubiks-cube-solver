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
    
private:
    using EMOVE = Rubiks::EMOVE;

    // moves to solve the even tetrad (ULB, DLF, DRB, URF)
    const std::array<std::vector<EMOVE>, 3> C_evenTetradSolvingMoves = {{
        { EMOVE::U2, EMOVE::L2, EMOVE::B2 },  // ULB
        { EMOVE::D2, EMOVE::F2 },             // DLF
        { EMOVE::R2 },                        // DRB
    }};
    // moves to solve ULF (first corner of the odd tetrad)
    const std::array<std::array<EMOVE, 4>, 3> C_oddTetradSolvingMoves = {{
        // these move sequences perform a double swap on the four pieces of  
        // the odd tetrad without affecting the corners in the even tetrad
        { EMOVE::F2, EMOVE::L2, EMOVE::F2, EMOVE::U2 },
        { EMOVE::U2, EMOVE::F2, EMOVE::U2, EMOVE::L2 },
        { EMOVE::L2, EMOVE::U2, EMOVE::L2, EMOVE::F2 },
    }};

    // imitates a move on an array
    void imitateMove(EMOVE move, std::array<uint8_t, 8>& tetradsPerm) const;
};

#endif // G2_G3_GOAL_H
