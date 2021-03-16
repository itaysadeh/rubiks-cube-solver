#ifndef G0_G1_DATABASE_H
#define G0_G1_DATABASE_H

#include "../../../Database/Database.h"

struct G0_G1_Database : public Database
{
	G0_G1_Database()
		// the orientation of the 12th edge can always be assumed, this is due to
		// the fact that it's only possible to flip the orientation of an even amount
		// of edges in one move: www.ryanheise.com/cube/cube_laws.html
		// this results in 2^12 / 2 = 2048 permutations of the orientations of the edges
		: Database(2048, "thistlethwaite_g0g1")
	{
	}

	uint32_t getIndex(const Rubiks& cube) const override;
};

#endif // G0_G1_DATABASE_H
