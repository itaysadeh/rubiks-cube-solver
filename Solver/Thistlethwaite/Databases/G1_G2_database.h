#ifndef G1_G2_DATABASE_H
#define G1_G2_DATABASE_H

#include "../../Database.h"
#include "../../../Util/Indexer.h"

struct G1_G2_Database : public Database
{
	G1_G2_Database()
        // 8C4 * 3^7 = 1082565
        : Database(1082565, "Thistlethwaite/G1")
	{
	}

	uint32_t getIndex(const Rubiks& cube) const override;

private:
    CombIndexer<4> combIndexer4;
};

#endif // G1_G2_DATABASE_H
