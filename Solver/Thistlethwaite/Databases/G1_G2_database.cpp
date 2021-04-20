#include "G1_G2_database.h"

uint32_t G1_G2_Database::getInd(const Rubiks& cube) const
{
    using EPIECE  = Rubiks::EPIECE;

    // stores the orientation of all corners (by position, regardless of which corner is where)
    std::array<uint8_t, 7> C_orientationPerm = {
        cube.getCornerOrientation(cube.getCorner(EPIECE::ULB)),
        cube.getCornerOrientation(cube.getCorner(EPIECE::ULF)),
        cube.getCornerOrientation(cube.getCorner(EPIECE::DLF)),
        cube.getCornerOrientation(cube.getCorner(EPIECE::DLB)),
        cube.getCornerOrientation(cube.getCorner(EPIECE::URF)),
        cube.getCornerOrientation(cube.getCorner(EPIECE::URB)),
        cube.getCornerOrientation(cube.getCorner(EPIECE::DRB))
    };

    // stores the edges that are currently occupying each position
    std::array<uint8_t, 12> E_perm = {
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
    std::array<uint8_t, 4> E_posComb;

    for (uint8_t i = 0, e = 0; i < 12 && e < 4; ++i)
    {
        // indices of the M-slice edges are 8, 9, 10, 11
        if (E_perm[i] == 8  || E_perm[i] == 9 ||
            E_perm[i] == 10 || E_perm[i] == 11)
        {
            E_posComb[e++] = i + 1;
        }
    }

    uint32_t E_ind = combIndexer4.getInd(E_posComb); // edge
    uint32_t C_ind = 0;                              // corner

    // treats corner orientations as ternary numbers and converts it to decimal
    C_ind +=
        C_orientationPerm[0] +
        C_orientationPerm[1] * 3 +
        C_orientationPerm[2] * 9 +
        C_orientationPerm[3] * 27 +
        C_orientationPerm[4] * 81 +
        C_orientationPerm[5] * 243 +
        C_orientationPerm[6] * 729;

    // (0..3^7 - 1) * 12C4 + (0..12C4 - 1) = 0..1082564
    return C_ind * 495 + E_ind;
}
