#pragma once

#include "../../../Database/Database.h"

struct G2_G3_Database : public Database
{
	G2_G3_Database()
		// 8C4^2 * 2 * 3 = 29400  
		: Database(29400, "thistlethwaite_g2g3")
		//: Database(576, "576_cornerPerms")
	{
	}

	uint32_t getIndex(const Rubiks& cube) const override;
};