#ifndef G2_G3_DATABASE_H
#define G2_G3_DATABASE_H

#include "../../database.h"
#include "../../../Util/indexer.h"

/*
 * In G3, a cube is solvable using 180-degre moves only. This means that all edges are in their
 * home slice and all corners are in their natural orbits. I couldn't find a nice way to rank each
 * corner state so I split the 2 tetrads into 4 pairs (like in Stefan's approach). Since the M-slice
 * is already solved in G2, a solved E-slice dictates a solved S-slice (vice versa), therefore only 8C4 edge
 * states are stored in the database. An extra factor of 2 is added due to parity (corners): All G3 states
 * have even parity because only 180-degre moves are allowed (even amount of twists), and G2 also stores states with odd parity.
 *
 * Therefore, there are 8C4 * (8C2 * 6C2 * 4C2 * 2C2) * 2 = 352800 states to store in the database.
 *
 * Stefan's approach: tomas.rokicki.com/cubecontest/stefan1.txt
*/


struct G2_G3_Database : public Database
{
	G2_G3_Database()
        : Database(29400, "Thistlethwaite/G2")
	{
	}

        uint32_t getInd(const Rubiks& cube) const override;

private:
    CombIndexer<4> combIndexer4;
    PermIndexer<3> permIndexer3;

    using EMOVE = Rubiks::EMOVE;

    // moves to solve the even tetrad (ULB, DLF, DRB, URF)
    const std::array<std::vector<EMOVE>, 3> C_evenTetradSolvingMoves = {{
        {EMOVE::U2, EMOVE::L2, EMOVE::B2},  // ULB
        {EMOVE::D2, EMOVE::F2},             // DLF
        {EMOVE::R2}                         // DRB
    }};
    // moves to solve ULF (first corner of the odd tetrad)
    const std::array<std::array<EMOVE, 4>, 3> C_oddTetradSolvingMoves = {{
        // these move sequences perform a double swap on the four pieces of  
        // the odd tetrad without affecting the corners in the even tetrad
        {EMOVE::F2, EMOVE::L2, EMOVE::F2, EMOVE::U2},
        {EMOVE::U2, EMOVE::F2, EMOVE::U2, EMOVE::L2},
        {EMOVE::L2, EMOVE::U2, EMOVE::L2, EMOVE::F2}
    }};
};

#endif // G2_G3_DATABASE_H
