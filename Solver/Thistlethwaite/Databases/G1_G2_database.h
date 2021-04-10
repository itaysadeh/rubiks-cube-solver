#ifndef G1_G2_DATABASE_H
#define G1_G2_DATABASE_H

#include "../../database.h"
#include "../../../Util/indexer.h"

/*
 * In G2, all the M-slice edges are brought back to their home slice and the orientation of all the corners
 * is solved (their Left or Right facelet is in the Left or Right face). There are 3 ways a corner can be
 * oriented which gives 3^8 corner states. Similar to the edges in G0, only 3^8 / 3 of the corner states are
 * actually reachable because the total orientation value of the corners is always divisible by 3. 8C4 for the edges
 * is for 8 positions where the 4 M-slice edges can be (without regard to order)
 *
 * Therefore, there are 8C4 * 3^8 / 3 = 8C4 * 3^7 = 1082565 states to store in a database.
*/

struct G1_G2_Database : public Database
{
	G1_G2_Database()
        : Database(1082565, "Thistlethwaite/G1")
	{
	}

        uint32_t getInd(const Rubiks& cube) const override;

private:
    CombIndexer<4> combIndexer4;
};

#endif // G1_G2_DATABASE_H
