#pragma once

#include "../../../Database/Database.h"
#include <bitset>

struct G0_G1_Database : public Database
{
	G0_G1_Database()
		// edge orientations^edges = 2^11 = 2048
		: Database(2048, "thistlethwaite_g0g1")
	{
	}

	uint32_t getIndex(const Rubiks& cube) const override;
};

