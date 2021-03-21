#include "G3_G4_database.h"

uint32_t G3_G4_Database::getIndex(const Rubiks& cube) const
{
    using EPIECE = Rubiks::EPIECE;

    // stores which edge is currently occupying each position in it's slice
    std::array<uint8_t, 4> ePosPermE = {
        cube.getPieceInd(EPIECE::LF),
        cube.getPieceInd(EPIECE::LB),
        cube.getPieceInd(EPIECE::RF),
        cube.getPieceInd(EPIECE::RB),
    };
    std::array<uint8_t, 4> ePosPermM = {
        cube.getPieceInd(EPIECE::UF),
        cube.getPieceInd(EPIECE::DF),
        cube.getPieceInd(EPIECE::DB),
        cube.getPieceInd(EPIECE::UB),
    };
    // only half the pieces in the S-slice
    std::array<uint8_t, 2> ePosPermS = {
        cube.getPieceInd(EPIECE::UL),
        cube.getPieceInd(EPIECE::DL),
    };

    // stores which corner is currently occupying which position in it's tetrad
    std::array<uint8_t, 4> cTetradPosPerm = {
        cube.getPieceInd(EPIECE::ULB),
        cube.getPieceInd(EPIECE::DLF),
        cube.getPieceInd(EPIECE::DRB),
        cube.getPieceInd(EPIECE::URF),
    };

    // sets the indices of all edge and corner pieces to a value between 0 and 3
    for (uint8_t& c : cTetradPosPerm) c >>= 1;
    for (uint8_t& e : ePosPermE) e &= 3;
    for (uint8_t& e : ePosPermM) e &= 3;
    // indices of the S-slice edges are 0..3 by default

    // rank of corner tetrads and edge slices
    uint8_t cTetradRank = cube.getPieceInd(EPIECE::ULF);
    uint8_t eSliceRankS = permIndexer4p2.getInd(ePosPermS);

    // (0..4! - 1) * 4 + 0..3 = 0..96
    uint32_t cInd = permIndexer4.getInd(cTetradPosPerm) * 4 + (cTetradRank >> 1);
    // (0..4! - 1) * (4!^2 / 2) + (0..4! - 1) * (4! / 2) + (0..4! / 2) = 0..6911
    uint32_t eInd = permIndexer4.getInd(ePosPermM) * 288 + permIndexer4.getInd(ePosPermE) * 12 + eSliceRankS;
    // 0..9611 * 96 + 0..95 = 0..663551
    return eInd * 96 + cInd;
}
