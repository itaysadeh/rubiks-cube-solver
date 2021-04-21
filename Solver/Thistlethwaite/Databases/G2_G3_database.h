#ifndef G2_G3_DATABASE_H
#define G2_G3_DATABASE_H

#include "../../database.h"
#include "../../../Util/indexer.h"

/*
 * In G3, a cube is solvable using 180-degree moves only. This means that all edges are in their
 * home slice and all corners are in their natural orbits. The M-slice is already solved in G1.
 * One solved slice / tetrad means that the second slice / tetrad is also solved, so the positions
 * of 4 edges and 4 corners are tracked (8C4 possible combinations for both)
 * 
 * Because of 90-degree L/R face turns, there are states in G2 that have odd parity which adds an
 * additional factor of 2.
 * 
 * Additionally, a factor of 3 is added which is explained here:
 * puzzling.stackexchange.com/questions/5402/what-is-the-meaning-of-a-tetrad-twist-in-thistlethwaites-algorithm
 *
 * Therefore, there are 8C4^2 * 2 * 6 = 29400 states to store in the database.
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

#endif // G2_G3_DATABASE_H
