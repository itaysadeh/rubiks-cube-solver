#ifndef G2_G3_DATABASE_H
#define G2_G3_DATABASE_H

#include "../../Database.h"
#include "../../../Util/Indexer.h"

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
        : Database(352800, "Thistlethwaite/G2")
	{
	}

	uint32_t getIndex(const Rubiks& cube) const override;

private:
    CombIndexer<4> combIndexer4;
};

#endif // G2_G3_DATABASE_H
