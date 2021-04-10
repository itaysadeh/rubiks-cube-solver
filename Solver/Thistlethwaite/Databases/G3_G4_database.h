#ifndef G3_G4_DATABASE_H
#define G3_G4_DATABASE_H

#include "../../database.h"
#include "../../../Util/indexer.h"

/*
 * In G3->G4, finally the cube is solved. In this state the cube is seperated to 3 edge slices
 * and 2 corner tetrads (each containing 4 pieces). Because only 180-degre moves are allowed the
 * pieces will never leave these orbits. Each slice/tetrad can be permuted in 4! ways which
 * gives 4!^5, but there are some restrictions:
 *
 * Corners: only 4!^2 / 6 of the corner states are reachable due to parity and disallowed lone 3-cycles.
 *
 * Edges: only 4!^4 / 2 of the edge states are reachable due to parity.
 *
 * Therefore, there are 4!^5 / 12 = 96 * 4!^3 / 2 = 663552 states to store in the database.
 *
 * disallowed lone 3-cycles explained here: puzzling.stackexchange.com/questions/5402/what-is-the-meaning-of-a-tetrad-twist-in-thistlethwaites-algorithm
*/

struct G3_G4_Database : public Database
{
	G3_G4_Database()
       : Database(663552, "Thistlethwaite/G3")
	{	
	}

        uint32_t getInd(const Rubiks& cube) const override;

private:
    PermIndexer<4> permIndexer4;
    PermIndexerPartial<4, 2> permIndexer4p2;
};

#endif // G3_G4_DATABASE_H
