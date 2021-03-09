#pragma once

#include "../../../Database/Database.h"

struct G2_G3_Database : public Database
{
	G2_G3_Database()
		// only 4 corners need to be checked to see whether all corners are in their natural
		// orbits (can be solved using 180-degree moves only) due to even parity.
		// because there's no regard to order, this results in 8C4 = 70 possible positions permutations
		// of the 4 corners.

		// there are 4! * 4! = 576 possible permutations of the corners within their natural orbits, but only
		// 96 of these permutations are reachable from a solved cube using G3 moves (180-degree moves only).
		// this results in an added factor of 6 (576 / 96 = 6) to G2.

		// similarly to the corners, to get the edges into their slices (notice that the 4 M-slice edges are
		// already solved) only half of the edge positions are possible due to even parity (there amount of 
		// unsolved edges will always be even).
		// this results in 8C4 = 70 possible permutations of the edges
		
		// 8C4^2 * 6 = 29400
		: Database(29400, "thistlethwaite_g2g3")
	{
	}

	uint32_t getIndex(const Rubiks& cube) const override;
};