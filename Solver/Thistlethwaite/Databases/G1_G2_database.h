#pragma once

#include "../../../Database/Database.h"

struct G1_G2_Database : public Database
{
	G1_G2_Database()
		// the orientation (0/1/2) of the 8th corner can always be assumed, this is due to
		// the fact that it's impossible to reach a state where the sum of all corner orientations
		// is not divisable by 3: www.ryanheise.com/cube/cube_laws.html
		// this results in 3^8 / 3 = 2187 possible orientations of the corners

		// the 4 M-slice edges need to be brough back into their slice, without regard to their order.
		// 4 edges in 12 positions gives 12C4 = 495 possible combinations of the 4 M-slice edges

		// 495 * 2187 = 1082565
		: Database(1082565, "thistlethwaite_g1g2")
	{
	}

	uint32_t getIndex(const Rubiks& cube) const override;
};
