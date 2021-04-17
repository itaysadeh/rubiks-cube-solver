#include "G2_G3_database.h"

uint32_t G2_G3_Database::getInd(const Rubiks& cube) const
{
    using EPIECE = Rubiks::EPIECE;
    using EMOVE  = Rubiks::EMOVE;

    // stores which edge is currently occupying which position on the E- and S-slices (M-slice was solved in G1)
    std::array<uint8_t, 8> E_perm = {
        cube.getPieceInd(EPIECE::UL),
        cube.getPieceInd(EPIECE::UR),
        cube.getPieceInd(EPIECE::DL),
        cube.getPieceInd(EPIECE::DR),
        cube.getPieceInd(EPIECE::RF),
        cube.getPieceInd(EPIECE::RB),
        cube.getPieceInd(EPIECE::LF),
        cube.getPieceInd(EPIECE::LB),
    };
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
        C_posPerm[C_perm[i]] = i;
    }

    // stores the positions of the 4 edges that need to be brought back to the E-slice
    // a solved E-slice dictates a solved S-slice (vice versa), only 1 slice has to be considered
    std::array<uint8_t, 4> E_posComb;
    // same as the edges, spliting the corners into 2 tetrads - one that contains all the corners
    // with even indices and one that contains all the corners with odd indices
    std::array<uint8_t, 4> C_posComb;
    // stores the relative order of the corners within their slices from the initial permutation
    std::array<uint8_t, 8> C_tetradsPerm;

    for (uint8_t i = 0, e = 0, c = 0, ce = 0, co = 1; i < 8; ++i)
    {
        // indices of the E-slice edges are 4, 5, 6, 7
        if (E_perm[i] == 4 || E_perm[i] == 5 ||
            E_perm[i] == 6 || E_perm[i] == 7)
        {
            E_posComb[e++] = i + 1;
        }
        // even tetrad
        if (C_perm[i] % 2 == 0)
        {
            C_posComb[c++] = i + 1;
        }
        // splits the corners into their tetrads
        if (C_posPerm[i] % 2 == 0)
        {
            C_tetradsPerm[ce] = C_posPerm[i];
            co += 2;
        }
        else
        {
            C_tetradsPerm[co] = C_posPerm[i];
            ce += 2;
        }
    }

    // imitate a move (half twists only) in an array
    auto imitateMove = [](EMOVE move, std::array<uint8_t, 8>& tetradsPerm) {
        switch (move)
        {
        case EMOVE::U2:
            std::swap(tetradsPerm[0], tetradsPerm[6]);
            std::swap(tetradsPerm[1], tetradsPerm[7]);
            break;
        case EMOVE::D2:
            std::swap(tetradsPerm[2], tetradsPerm[4]);
            std::swap(tetradsPerm[3], tetradsPerm[5]);
            break;
        case EMOVE::L2:
            std::swap(tetradsPerm[0], tetradsPerm[2]);
            std::swap(tetradsPerm[1], tetradsPerm[3]);
            break;
        case EMOVE::R2:
            std::swap(tetradsPerm[4], tetradsPerm[6]);
            std::swap(tetradsPerm[5], tetradsPerm[7]);
            break;
        case EMOVE::F2:
            std::swap(tetradsPerm[2], tetradsPerm[6]);
            std::swap(tetradsPerm[1], tetradsPerm[5]);
            break;
        case EMOVE::B2:
            std::swap(tetradsPerm[0], tetradsPerm[4]);
            std::swap(tetradsPerm[3], tetradsPerm[7]);
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
        if (C_tetradsPerm[i] == i) continue;

        for (auto move : C_evenTetradSolvingMoves[i / 2])
        {
            // tries to solve
            imitateMove(move, C_tetradsPerm);

            if (C_tetradsPerm[i] == i) break;
            // reverse move if it didn't solve the corner
            else imitateMove(move, C_tetradsPerm);
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
    if (C_tetradsPerm[1] != 1)
    {
        for (uint8_t i = 0; i < 3; ++i)
        {
            // tries to solve
            for (auto it = C_oddTetradSolvingMoves[i].begin();
                      it != C_oddTetradSolvingMoves[i].end(); ++it)
            {
                imitateMove(*it, C_tetradsPerm);
            }

            if (C_tetradsPerm[1] == 1) break;
            // reverse move if it didn't solve the corner
            for (auto rit = C_oddTetradSolvingMoves[i].rbegin();
                      rit != C_oddTetradSolvingMoves[i].rend(); ++rit)
            {
                imitateMove(*rit, C_tetradsPerm);
            }
        }
    }

    // permutation of the remaining 3 corners in the odd tetrad (3, 5, 7)
    std::array<uint8_t, 3> C_oddTetradPerm = {
        (uint8_t)((C_tetradsPerm[3] >> 1) - 1),
        (uint8_t)((C_tetradsPerm[5] >> 1) - 1),
        (uint8_t)((C_tetradsPerm[7] >> 1) - 1),
    };

    // 0..8C4 - 1
    uint32_t E_ind = combIndexer4.getInd(E_posComb);
    // 0..8C4 - 1
    uint32_t C_ind = combIndexer4.getInd(C_posComb);
    // 0..3! - 1
    uint32_t F_ind = permIndexer3.getInd(C_oddTetradPerm);

    // (0..8C4 - 1 * 8C4 + 0..8C4 - 1) * 6 + 0..5 = 0..29399
    return (C_ind * 70 + E_ind) * 6 + F_ind;
}
