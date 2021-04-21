#include "G2_G3_goal.h"

bool G2_G3_Goal::contented(const Rubiks& cube) const
{
    using ECOLOUR = Rubiks::ECOLOUR;
    using EPIECE  = Rubiks::EPIECE;
    using EEDGE   = Rubiks::EEDGE;

    // stores which corner is currently occupying which position
    std::array<uint8_t, 8> C_perm = {
        cube.getPieceInd(EPIECE::ULB),
        cube.getPieceInd(EPIECE::ULF),
        cube.getPieceInd(EPIECE::DLF),
        cube.getPieceInd(EPIECE::DLB),
        cube.getPieceInd(EPIECE::DRB),
        cube.getPieceInd(EPIECE::DRF),
        cube.getPieceInd(EPIECE::URF),
        cube.getPieceInd(EPIECE::URB),
    };
    
    // checks whether the tetrads are formed
    for (int i = 0; i < 8; ++i) if (C_perm[i] % 2 != i % 2) return false;

    // a corner permutation is in G3 if all corners are solved after solving 5 corners

    // solves the even tetrad (ULB = 0, DLF = 2, DRB = 4, URF = 6)
    for (uint8_t i = 0; i < 6; i += 2)
    {
        if (C_perm[i] == i) continue;

        for (auto move : C_evenTetradSolvingMoves[i / 2])
        {
            imitateMove(move, C_perm);
            if (C_perm[i] == i) break;    
            imitateMove(move, C_perm);
        }
    }
    // solves one corner in the odd tetrad (ULF = 1)
    uint8_t move_sequence = 0;
    while (C_perm[1] != 1)
    {
        for (int j = 0; j < 4; ++j)
        {
            imitateMove(C_oddTetradSolvingMoves[move_sequence][j], C_perm);
        }
        if (C_perm[1] == 1) break;
        for (int j = 3; j >= 0; --j)
        {
            imitateMove(C_oddTetradSolvingMoves[move_sequence][j], C_perm);
        }
        move_sequence++;
    }

    // checks if the permutation is solved
    for (uint8_t i = 0; i < 8; ++i) if (C_perm[i] != i) return false;

    // checks if all the edges are in their home slice (M-slice edges are already solved)
    return
        (cube.getColour(EEDGE::UR) == ECOLOUR::W || cube.getColour(EEDGE::UR) == ECOLOUR::Y) &&
        (cube.getColour(EEDGE::UL) == ECOLOUR::W || cube.getColour(EEDGE::UL) == ECOLOUR::Y) &&
        (cube.getColour(EEDGE::DR) == ECOLOUR::W || cube.getColour(EEDGE::DR) == ECOLOUR::Y) &&
        (cube.getColour(EEDGE::DL) == ECOLOUR::W || cube.getColour(EEDGE::DL) == ECOLOUR::Y) &&
        (cube.getColour(EEDGE::FR) == ECOLOUR::G || cube.getColour(EEDGE::FR) == ECOLOUR::B) &&
        (cube.getColour(EEDGE::FL) == ECOLOUR::G || cube.getColour(EEDGE::FL) == ECOLOUR::B) &&
        (cube.getColour(EEDGE::BR) == ECOLOUR::G || cube.getColour(EEDGE::BR) == ECOLOUR::B) &&
        (cube.getColour(EEDGE::BL) == ECOLOUR::G || cube.getColour(EEDGE::BL) == ECOLOUR::B);
}

void G2_G3_Goal::imitateMove(EMOVE move, std::array<uint8_t, 8>& tetradsPerm) const
{
    std::array<uint8_t, 4> indices, positions;
    switch (move)
    {
    case EMOVE::U2:
        indices = { 0,6,1,7 };
        break;
    case EMOVE::D2:
        indices = { 2,4,3,5 };
        break;
    case EMOVE::L2:
        indices = { 0,2,1,3 };
        break;
    case EMOVE::R2:
        indices = { 4,6,5,7 };
        break;
    case EMOVE::F2:
        indices = { 2,6,1,5 };
        break;
    case EMOVE::B2:
        indices = { 0,4,3,7 };
        break;
    default:
        std::string moveValue = std::to_string((int)move);
        throw std::logic_error("G2_G3_Goal::imitateMove invalid enum value " + moveValue);
    }

    for (uint8_t i = 0; i < 8; ++i)
    {
        if (tetradsPerm[i] == indices[0]) positions[0] = i;
        if (tetradsPerm[i] == indices[1]) positions[1] = i;
        if (tetradsPerm[i] == indices[2]) positions[2] = i;
        if (tetradsPerm[i] == indices[3]) positions[3] = i;
    }

    std::swap(tetradsPerm[positions[0]], tetradsPerm[positions[1]]);
    std::swap(tetradsPerm[positions[2]], tetradsPerm[positions[3]]);
}