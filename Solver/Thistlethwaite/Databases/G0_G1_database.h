#ifndef G0_G1_DATABASE_H
#define G0_G1_DATABASE_H

#include "../../Database.h"

struct G0_G1_Database : public Database
{
	G0_G1_Database()
        // 2^11 = 2048
        : Database(2048, "Thistlethwaite/G0")
	{
	}

	uint32_t getIndex(const Rubiks& cube) const override;
};

#endif // G0_G1_DATABASE_H
