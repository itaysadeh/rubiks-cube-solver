#ifndef G3_G4_DATABASE_H
#define G3_G4_DATABASE_H

#include "../../../Database/Database.h"

struct G3_G4_Database : public Database
{
	G3_G4_Database()
		: Database(663552, "thistlethwaite_g3g4")
	{	
	}

	uint32_t getIndex(const Rubiks& cube) const override;
};

#endif // G3_G4_DATABASE_H
