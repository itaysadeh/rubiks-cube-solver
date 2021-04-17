#include "G2_G3_goal.h"

bool G2_G3_Goal::contented(const Rubiks& cube) const
{
    using ECOLOUR = Rubiks::ECOLOUR;
    using EPIECE  = Rubiks::EPIECE;
    using EEDGE   = Rubiks::EEDGE;
    using EMOVE   = Rubiks::EMOVE;

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

    // stores the positions of the corners ((perm[pos] = ind) -> (perm[ind] = pos))
    std::array<uint8_t, 8> C_posPerm;
    for (int i = 0; i < 8; ++i)
    {
        // checks if the tetrads are formed
        if ((C_perm[i] & 1) != (i & 1)) return false;

        // convers to a piece->position relation
        C_posPerm[C_perm[i]] = i;
    }

    // a corner permutation is in G3 if all corners are solved after solving 5 corners

     // imitate a move (half twists only) in an array
    auto imitateMove = [](EMOVE move, std::array<uint8_t, 8>& perm) {
        switch (move)
        {
        case EMOVE::U2:
            std::swap(perm[0], perm[6]);
            std::swap(perm[1], perm[7]);
            break;
        case EMOVE::D2:
            std::swap(perm[2], perm[4]);
            std::swap(perm[3], perm[5]);
            break;
        case EMOVE::L2:
            std::swap(perm[0], perm[2]);
            std::swap(perm[1], perm[3]);
            break;
        case EMOVE::R2:
            std::swap(perm[4], perm[6]);
            std::swap(perm[5], perm[7]);
            break;
        case EMOVE::F2:
            std::swap(perm[2], perm[6]);
            std::swap(perm[1], perm[5]);
            break;
        case EMOVE::B2:
            std::swap(perm[0], perm[4]);
            std::swap(perm[3], perm[7]);
            break;
        default:
            std::string moveName = std::to_string((int)move);
            throw std::logic_error("G2_G3_database::getInd invalid enum value " + moveName);
        }
    };

    // moves to solve the even tetrad (ULB, DLF, DRB, URF)
    const std::array<std::vector<EMOVE>, 3> C_evenTetradSolvingMoves = {{
        {EMOVE::U2, EMOVE::L2, EMOVE::B2},  // ULB
        {EMOVE::D2, EMOVE::F2},             // DLF
        {EMOVE::R2}                         // DRB
    }};

    // run the moves to solve the even tetrad
    for (uint8_t i = 0; i < 6; i += 2)
    {
        // checks if a corner is solved
        if (C_posPerm[i] == i) continue;

        for (auto move : C_evenTetradSolvingMoves[i / 2])
        {
            // tries to solve
            imitateMove(move, C_posPerm);

            if (C_posPerm[i] == i) break;
            // reverse move if it didn't solve the corner
            else imitateMove(move, C_posPerm);
        }
    }

    // moves to solve ULF (first corner of the odd tetrad)
    std::array<std::array<EMOVE, 4>, 3> C_oddTetradSolvingMoves = {{
        // these move sequences perform a double swap on the four pieces of  
        // the odd tetrad without affecting the corners in the even tetrad
        {EMOVE::F2, EMOVE::L2, EMOVE::F2, EMOVE::U2},
        {EMOVE::U2, EMOVE::F2, EMOVE::U2, EMOVE::L2},
        {EMOVE::L2, EMOVE::U2, EMOVE::L2, EMOVE::F2}
    }};

    // solve ULF if it's not already solved
    if (C_posPerm[1] != 1)
    {
        for (uint8_t i = 0; i < 3; ++i)
        {
            // tries to solve
            for (auto it = C_oddTetradSolvingMoves[i].begin();
                      it != C_oddTetradSolvingMoves[i].end(); ++it)
            {
                imitateMove(*it, C_posPerm);
            }

            if (C_posPerm[1] == 1) break;
            // reverse move if it didn't solve the corner
            for (auto rit = C_oddTetradSolvingMoves[i].rbegin();
                      rit != C_oddTetradSolvingMoves[i].rend(); ++rit)
            {
                imitateMove(*rit, C_posPerm);
            }
        }
    }

    // checks if the permutation is solved
    for (uint8_t i = 0; i < 8; ++i)
    {
        if (C_posPerm[i] != i) return false;
    }

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
