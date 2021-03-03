#pragma once

#include <memory>
#include <iostream>

#include "G0_G1_database.h"
#include "G1_G2_database.h"
#include "G2_G3_database.h"
#include "G3_G4_database.h"

#include "G0_G1_goal.h"
#include "G1_G2_goal.h"
#include "G2_G3_goal.h"
#include "G3_G4_goal.h"

#include "../../../Util/DatabaseGenerator.h"

// base class for a group to use for polymorphysm in solvers and database generations
// contains a database and a goal for a group, and loads databases / generates them
struct Group
{
    void loadDatabase()
    {
        // TEMPORARY
        if (goal->name != "G0 to G1" && goal->name != "G1 to G2" && goal->name != "Gu2 to G3")
        {
            return;
        }

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