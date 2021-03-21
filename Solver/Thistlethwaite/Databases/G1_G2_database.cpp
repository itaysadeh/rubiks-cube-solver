#include "G1_G2_database.h"

uint32_t G1_G2_Database::getIndex(const Rubiks& cube) const
{
    using EPIECE  = Rubiks::EPIECE;
    using ECORNER = Rubiks::ECORNER;

    // stores the orientation of all corners (by position, regardless of which corner is where)
    std::array<uint8_t, 7> cOrientationPerm = {
        //  face:                 {               L/R                          U/D                            F/B            }
        cube.getCornerOrientation({ cube.getColour(ECORNER::LUB), cube.getColour(ECORNER::ULB), cube.getColour(ECORNER::BLU) }),
        cube.getCornerOrientation({ cube.getColour(ECORNER::LUF), cube.getColour(ECORNER::ULF), cube.getColour(ECORNER::FLU) }),
        cube.getCornerOrientation({ cube.getColour(ECORNER::LDF), cube.getColour(ECORNER::DLF), cube.getColour(ECORNER::FLD) }),
        cube.getCornerOrientation({ cube.getColour(ECORNER::LDB), cube.getColour(ECORNER::DLB), cube.getColour(ECORNER::BLD) }),
        cube.getCornerOrientation({ cube.getColour(ECORNER::RUF), cube.getColour(ECORNER::URF), cube.getColour(ECORNER::FRU) }),
        cube.getCornerOrientation({ cube.getColour(ECORNER::RUB), cube.getColour(ECORNER::URB), cube.getColour(ECORNER::BRU) }),
        cube.getCornerOrientation({ cube.getColour(ECORNER::RDB), cube.getColour(ECORNER::DRB), cube.getColour(ECORNER::BRD) })
    };

    // stores the edges that are currently occupying each position
    // the first 4 positions are in the M-slice in order to make a solved state the lowest combination: 0,1,2,3
    std::array<uint8_t, 12> ePosPerm = {
        cube.getPieceInd(EPIECE::UB),
        cube.getPieceInd(EPIECE::UF),
        cube.getPieceInd(EPIECE::DB),
        cube.getPieceInd(EPIECE::DF),
        cube.getPieceInd(EPIECE::UR),
        cube.getPieceInd(EPIECE::UL),
        cube.getPieceInd(EPIECE::DR),
        cube.getPieceInd(EPIECE::DL),
        cube.getPieceInd(EPIECE::RF),
        cube.getPieceInd(EPIECE::LF),
        cube.getPieceInd(EPIECE::RB),
        cube.getPieceInd(EPIECE::LB)
    };

    // stores the positions of the 4 edges that need to be brought back to the M-slice
    std::array<uint8_t, 4> ePosComb;

    for (uint8_t i = 0, e = 0; i < 12 && e < 4; ++i)
    {
        // indices of the M-slice edges are 8, 9, 10, 11
        if (ePosPerm[i] == 8  || ePosPerm[i] == 9 ||
            ePosPerm[i] == 10 || ePosPerm[i] == 11)
        {
            ePosComb[e++] = i + 1;
        }
    }

    uint32_t eInd = combIndexer4.getInd(ePosComb); // edge
    uint32_t cInd = 0;                             // corner

    // treats corner orientations as ternary numbers and converts it to decimal
    cInd +=
        cOrientationPerm[0] +
        cOrientationPerm[1] * 3 +
        cOrientationPerm[2] * 9 +
        cOrientationPerm[3] * 27 +
        cOrientationPerm[4] * 81 +
        cOrientationPerm[5] * 243 +
        cOrientationPerm[6] * 729;

    // (0..3^7 - 1) * 12C4 + (0..12C4 - 1) = 0..1082565
    return cInd * 495 + eInd;
}
