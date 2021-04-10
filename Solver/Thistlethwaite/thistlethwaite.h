#ifndef THISTLETHWAITE_H
#define THISTLETHWAITE_H

#include "../solver.h"
#include "groups.h"

// jaapsch.net/puzzles/thistle.htm
class Thistlethwaite : public Solver
{
public:
    using EMOVE = Rubiks::EMOVE;

	Thistlethwaite();

	std::vector<EMOVE> solve(const Rubiks& cube) const override;

private:
	using G0_G1 = TypedGroup<G0_G1_Database, G0_G1_Goal>;
	using G1_G2 = TypedGroup<G1_G2_Database, G1_G2_Goal>;
	using G2_G3 = TypedGroup<G2_G3_Database, G2_G3_Goal>;
	using G3_G4 = TypedGroup<G3_G4_Database, G3_G4_Goal>;
    
	G0_G1 m_G0G1;
	G1_G2 m_G1G2;
	G2_G3 m_G2G3;
	G3_G4 m_G3G4;

	std::vector<Group*> m_groups;
};

#endif // THISTLETHWAITE_H
