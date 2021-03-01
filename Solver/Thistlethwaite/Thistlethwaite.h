#pragma once

#include "../Solver.h"
#include "Groups/Groups.h"

class Thistlethwaite : public Solver
{
public:
	std::vector<EMOVE> solve(const Rubiks& cube);// override;

	// TEMPORARY
	Thistlethwaite();

private:
	using G0_G1 = TypedGroup<G0_G1_Database, G0_G1_Goal>;
	using G1_G2 = TypedGroup<G1_G2_Database, G1_G2_Goal>;
	using G2_G3 = TypedGroup<G2_G3_Database, G2_G3_Goal>;
	using G3_G4 = TypedGroup<G3_G4_Database, G3_G4_Goal>;

	G0_G1 m_G0G1;
	G1_G2 m_G1G2;
	G2_G3 m_G2G3;
	G3_G4 m_G3G4;
};

