#include "G1_G2_goal.h"

bool G1_G2_Goal::contented(const Rubiks& cube) const
{
    using ECOLOUR   = Rubiks::ECOLOUR;
    using EEDGE     = Rubiks::EEDGE;
    using ECORNER   = Rubiks::ECORNER;

    // M-slice edges
    ECOLOUR E_FU = cube.getColour(EEDGE::FU);
    ECOLOUR E_FD = cube.getColour(EEDGE::FD);
    ECOLOUR E_BU = cube.getColour(EEDGE::BU);
    ECOLOUR E_BD = cube.getColour(EEDGE::BD);

    ECOLOUR E_UF = cube.getColour(EEDGE::UF);
    ECOLOUR E_DF = cube.getColour(EEDGE::DF);
    ECOLOUR E_UB = cube.getColour(EEDGE::UB);
    ECOLOUR E_DB = cube.getColour(EEDGE::DB);

    // corner facelets from the L/R axis
    ECOLOUR C_LFU = cube.getColour(ECORNER::LUF);
    ECOLOUR C_LUB = cube.getColour(ECORNER::LUB);
    ECOLOUR C_LDF = cube.getColour(ECORNER::LDF);
    ECOLOUR C_LBD = cube.getColour(ECORNER::LDB);
    ECOLOUR C_RBU = cube.getColour(ECORNER::RUB);
    ECOLOUR C_RDB = cube.getColour(ECORNER::RDB);
    ECOLOUR C_RFD = cube.getColour(ECORNER::RDF);
    ECOLOUR C_RUF = cube.getColour(ECORNER::RUF);

    return
        // checks that the M-slice edges are in the M-slice
        (E_FU == ECOLOUR::G || E_FU == ECOLOUR::B) && (E_UF == ECOLOUR::W || E_UF == ECOLOUR::Y) &&
        (E_FD == ECOLOUR::G || E_FD == ECOLOUR::B) && (E_DF == ECOLOUR::W || E_DF == ECOLOUR::Y) &&
        (E_BU == ECOLOUR::G || E_BU == ECOLOUR::B) && (E_UB == ECOLOUR::W || E_UB == ECOLOUR::Y) &&
        (E_BD == ECOLOUR::G || E_BD == ECOLOUR::B) && (E_DB == ECOLOUR::W || E_DB == ECOLOUR::Y) &&
        // checks that the corners are oriented (their L/R facelet is in the L/R face)
        (C_LFU == ECOLOUR::O || C_LFU == ECOLOUR::R) && (C_LUB == ECOLOUR::O || C_LUB == ECOLOUR::R) &&
        (C_LDF == ECOLOUR::O || C_LDF == ECOLOUR::R) && (C_LBD == ECOLOUR::O || C_LBD == ECOLOUR::R) &&
        (C_RBU == ECOLOUR::O || C_RBU == ECOLOUR::R) && (C_RDB == ECOLOUR::O || C_RDB == ECOLOUR::R) &&
        (C_RFD == ECOLOUR::O || C_RFD == ECOLOUR::R) && (C_RUF == ECOLOUR::O || C_RUF == ECOLOUR::R);
}
