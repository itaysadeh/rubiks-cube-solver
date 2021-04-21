#ifndef G0_G1_DATABASE_H
#define G0_G1_DATABASE_H

#include "../../database.h"

/*
 * In G1, the orientation of all 12 edges is solved (good orientation means an edge can be solved
 * without using a 90-degree Up or Down move) G0->G1 only looks at edge orientations (0 for good, 1 for bad),
 * which gives 2^12 unique states. Only half of these states is reachable because the total edge orientation
 * value is always even (each move affects 0 or 4 edges which gives an overall even value).
 *
 * Therefore, there are 2^12 / 2 = 2^11 = 2048 states to store in a database.
*/

struct G0_G1_Database : public Database
{
	G0_G1_Database()
        : Database(2048, "Thistlethwaite/G0")
	{
	}

	uint32_t getInd(const Rubiks& cube) const override;
};

#endif // G0_G1_DATABASE_H
