#ifndef GROUPS_H
#define GROUPS_H

#include <memory>
#include <iostream>

#include "Databases/G0_G1_database.h"
#include "Databases/G1_G2_database.h"
#include "Databases/G2_G3_database.h"
#include "Databases/G3_G4_database.h"

#include "Goals/G0_G1_goal.h"
#include "Goals/G1_G2_goal.h"
#include "Goals/G2_G3_goal.h"
#include "Goals/G3_G4_goal.h"

#include "../../Util/DatabaseGenerator.h"

// base class for a group to use for polymorphysm in solvers and database generations
// contains a database and a goal for a group, and loads databases / generates them
struct Group
{
    void loadDatabase()
    {
        // load database
        std::cout << "Loading database for " << goal->name << "...\n";
        if (database->load())
        {
            std::cout << "Loaded database for " << goal->name << " successfully.\n";
        }
        else
        {
            // generate a new database if a database file is not provided
            std::cout << "Failed to load database for " << goal->name << ". generating:\n";
            DatabaseGenerator databaseGen;
            databaseGen.generate(*goal, *database);
        }
    }

    bool	  useDatabase = false;
    Database* database    = nullptr;
    Goal*     goal        = nullptr;
};

template<typename DatabaseType, typename GoalType>
struct TypedGroup : public Group
{
    TypedGroup()
    {
        database = &m_database;
        goal	 = &m_goal;
    }

private:
    DatabaseType m_database;
    GoalType m_goal;
};

#endif // GROUPS_H
