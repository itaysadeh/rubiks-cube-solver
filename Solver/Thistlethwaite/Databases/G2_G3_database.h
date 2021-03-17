#ifndef G2_G3_DATABASE_H
#define G2_G3_DATABASE_H

#include "../../Database.h"
#include "../../../Util/Indexer.h"

struct G2_G3_Database : public Database
{
	G2_G3_Database()
        // 8C4 * (8C2 * 6C2 * 4C2 * 2C2) * 2 = 70 * 2520 * 2 = 352800
        : Database(352800, "Thistlethwaite/G2")
	{
	}

	uint32_t getIndex(const Rubiks& cube) const override;

private:
    CombIndexer<4> combIndexer;
};

#endif // G2_G3_DATABASE_H
