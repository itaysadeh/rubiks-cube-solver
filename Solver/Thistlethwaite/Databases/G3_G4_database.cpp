#include "G3_G4_database.h"

uint32_t G3_G4_Database::getInd(const Rubiks& cube) const
{
    using EPIECE = Rubiks::EPIECE;

    // stores which edge is currently occupying each position in it's slice
    
    // E-slice
    std::array<uint8_t, 4> E_posPermE = {
        cube.getPieceInd(EPIECE::LF),
        cube.getPieceInd(EPIECE::LB),
        cube.getPieceInd(EPIECE::RF),
        cube.getPieceInd(EPIECE::RB),
    };
    // M-slice
    std::array<uint8_t, 4> E_posPermM = {
        cube.getPieceInd(EPIECE::UF),
        cube.getPieceInd(EPIECE::DF),
        cube.getPieceInd(EPIECE::DB),
        cube.getPieceInd(EPIECE::UB),
    };
    // S-slice
    // only half the pieces in the S-slice are stored, the positions of the first 10
    // edges dictate the positions of the last 2 (they have to have even parity)
    std::array<uint8_t, 2> E_posPermS = {
        cube.getPieceInd(EPIECE::UL),
        cube.getPieceInd(EPIECE::DL),
    };

    // stores which corner is currently occupying which position in it's tetrad
    std::array<uint8_t, 4> C_tetradPosPerm = {
        cube.getPieceInd(EPIECE::ULB),
        cube.getPieceInd(EPIECE::DLF),
        cube.getPieceInd(EPIECE::DRB),
        cube.getPieceInd(EPIECE::URF),
    };

    // sets the indices of all edge and corner pieces to a value between 0 and 3
    for (auto& c : C_tetradPosPerm) c >>= 1;
    for (auto& e : E_posPermE) e &= 3;
    for (auto& e : E_posPermM) e &= 3;
    // indices of the S-slice edges are 0..3 by default

    // for every permutation of the first tetrad the second tetrad will start 
    // with either 0/1/2/3 which dictates the "rank" of the permutation
    uint8_t C_tetradRank = cube.getPieceInd(EPIECE::ULF);
    uint8_t E_sliceRankS = permIndexer4p2.getInd(E_posPermS);

    // (0..4! - 1) * 4 + 0..3 = 0..96
    uint32_t C_ind = permIndexer4.getInd(C_tetradPosPerm) * 4 + (C_tetradRank >> 1);
    // (0..4! - 1) * (4!^2 / 2) + (0..4! - 1) * (4! / 2) + (0..4! / 2) = 0..6911
    uint32_t E_ind = permIndexer4.getInd(E_posPermM) * 288 + permIndexer4.getInd(E_posPermE) * 12 + E_sliceRankS;
    // 0..9611 * 96 + 0..95 = 0..663551
    return E_ind * 96 + C_ind;
}
