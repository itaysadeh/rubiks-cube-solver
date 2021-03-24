#include "G0_G1_goal.h"

bool G0_G1_Goal::contented(const Rubiks& cube) const
{
    using ECOLOUR   = Rubiks::ECOLOUR;
    using EEDGE     = Rubiks::EEDGE;

    ECOLOUR E_UB = cube.getColour(EEDGE::UB);
    ECOLOUR E_UR = cube.getColour(EEDGE::UR);
    ECOLOUR E_UF = cube.getColour(EEDGE::UF);
    ECOLOUR E_UL = cube.getColour(EEDGE::UL);

    ECOLOUR E_LU = cube.getColour(EEDGE::LU);
    ECOLOUR E_LF = cube.getColour(EEDGE::LF);
    ECOLOUR E_LD = cube.getColour(EEDGE::LD);
    ECOLOUR E_LB = cube.getColour(EEDGE::LB);

    ECOLOUR E_FU = cube.getColour(EEDGE::FU);
    ECOLOUR E_FR = cube.getColour(EEDGE::FR);
    ECOLOUR E_FD = cube.getColour(EEDGE::FD);
    ECOLOUR E_FL = cube.getColour(EEDGE::FL);

    ECOLOUR E_RU = cube.getColour(EEDGE::RU);
    ECOLOUR E_RB = cube.getColour(EEDGE::RB);
    ECOLOUR E_RD = cube.getColour(EEDGE::RD);
    ECOLOUR E_RF = cube.getColour(EEDGE::RF);

    ECOLOUR E_BU = cube.getColour(EEDGE::BU);
    ECOLOUR E_BL = cube.getColour(EEDGE::BL);
    ECOLOUR E_BD = cube.getColour(EEDGE::BD);
    ECOLOUR E_BR = cube.getColour(EEDGE::BR);

    ECOLOUR E_DF = cube.getColour(EEDGE::DF);
    ECOLOUR E_DR = cube.getColour(EEDGE::DR);
    ECOLOUR E_DB = cube.getColour(EEDGE::DB);
    ECOLOUR E_DL = cube.getColour(EEDGE::DL);

    // same logic from Rubiks::getEdgeOrientation
    return 
        ((E_FR == ECOLOUR::B || E_FR == ECOLOUR::G) || ((E_FR == ECOLOUR::W || E_FR == ECOLOUR::Y) && (E_RF == ECOLOUR::O || E_RF == ECOLOUR::R))) &&
        ((E_FL == ECOLOUR::B || E_FL == ECOLOUR::G) || ((E_FL == ECOLOUR::W || E_FL == ECOLOUR::Y) && (E_LF == ECOLOUR::O || E_LF == ECOLOUR::R))) &&
        ((E_FU == ECOLOUR::B || E_FU == ECOLOUR::G) || ((E_FU == ECOLOUR::W || E_FU == ECOLOUR::Y) && (E_UF == ECOLOUR::O || E_UF == ECOLOUR::R))) &&
        ((E_FD == ECOLOUR::B || E_FD == ECOLOUR::G) || ((E_FD == ECOLOUR::W || E_FD == ECOLOUR::Y) && (E_DF == ECOLOUR::O || E_DF == ECOLOUR::R))) &&

        ((E_BR == ECOLOUR::B || E_BR == ECOLOUR::G) || ((E_BR == ECOLOUR::W || E_BR == ECOLOUR::Y) && (E_RB == ECOLOUR::O || E_RB == ECOLOUR::R))) &&
        ((E_BL == ECOLOUR::B || E_BL == ECOLOUR::G) || ((E_BL == ECOLOUR::W || E_BL == ECOLOUR::Y) && (E_LB == ECOLOUR::O || E_LB == ECOLOUR::R))) &&
        ((E_BU == ECOLOUR::B || E_BU == ECOLOUR::G) || ((E_BU == ECOLOUR::W || E_BU == ECOLOUR::Y) && (E_UB == ECOLOUR::O || E_UB == ECOLOUR::R))) &&
        ((E_BD == ECOLOUR::B || E_BD == ECOLOUR::G) || ((E_BD == ECOLOUR::W || E_BD == ECOLOUR::Y) && (E_DB == ECOLOUR::O || E_DB == ECOLOUR::R))) &&

        ((E_RU == ECOLOUR::R || E_RU == ECOLOUR::O) || ((E_RU == ECOLOUR::W || E_RU == ECOLOUR::Y) && (E_UR == ECOLOUR::B || E_UR == ECOLOUR::G))) &&
        ((E_RD == ECOLOUR::R || E_RD == ECOLOUR::O) || ((E_RD == ECOLOUR::W || E_RD == ECOLOUR::Y) && (E_DR == ECOLOUR::B || E_DR == ECOLOUR::G))) &&
        ((E_LU == ECOLOUR::R || E_LU == ECOLOUR::O) || ((E_LU == ECOLOUR::W || E_LU == ECOLOUR::Y) && (E_UL == ECOLOUR::B || E_UL == ECOLOUR::G))) &&
        ((E_LD == ECOLOUR::R || E_LD == ECOLOUR::O) || ((E_LD == ECOLOUR::W || E_LD == ECOLOUR::Y) && (E_DL == ECOLOUR::B || E_DL == ECOLOUR::G)));
}
