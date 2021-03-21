#ifndef G3_G4_DATABASE_H
#define G3_G4_DATABASE_H

#include "../../Database.h"
#include "../../../Util/Indexer.h"

struct G3_G4_Database : public Database
{
	G3_G4_Database()
        // 96 * 4!^3 / 2 = 663552
       : Database(663552, "Thistlethwaite/G3")
	{	
	}

	uint32_t getIndex(const Rubiks& cube) const override;

private:
    PermIndexer<4> permIndexer4;
    PermIndexerPartial<4, 2> permIndexer4p2;
};

#endif // G3_G4_DATABASE_H
