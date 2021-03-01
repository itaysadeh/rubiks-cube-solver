#pragma once

#include "../../../../Database/Database.h"

struct G1_G2_Database : public Database
{
	G1_G2_Database()
		// 2187 = 3^7  = corner orientations permutations
		// 495	= 12C4 = possible arrangements of the 4 edges on the M slice among the 12 edges
		// 2187 * 495 = 1082565
		: Database(1082565, "thistlethwaite_g1g2")
	{
	}

	uint32_t getIndex(const Rubiks& cube) const override;
};
