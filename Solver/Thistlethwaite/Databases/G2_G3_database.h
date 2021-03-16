#ifndef G2_G3_DATABASE_H
#define G2_G3_DATABASE_H

#include "../../../Database/Database.h"
#include "../../../Util/Indexer.h"

struct G2_G3_Database : public Database
{
	G2_G3_Database()
        // 8 edges need to be brought back to their home slices (E and S slice)
        // since the M-slice is already solved. once 1 slice is solved, so is the
        // other so only 1 slice is checked resulting in 8C4 = 70 for the edges

        // 8 corners are split into 4 pairs, without regard to order (0:1 = 1:0)
        // 8C2 * 6C2 * 4C2 * 2C2 = 2520 for the corners

        // an additional factor of 2 is added due to parity
		
        // 70 * 2520 * 2 = 352800
        : Database(352800, "thistlethwaite_g2g3")
	{
	}

	uint32_t getIndex(const Rubiks& cube) const override;

private:
    CombIndexer<4> indexer;
};

#endif // G2_G3_DATABASE_H
