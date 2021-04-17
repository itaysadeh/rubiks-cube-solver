#include "G2_G3_database.h"

uint32_t G2_G3_Database::getInd(const Rubiks& cube) const
{
    using EPIECE = Rubiks::EPIECE;
    using EMOVE  = Rubiks::EMOVE;

    // stores which edge is currently occupying which position on the E- and S-slices (M-slice was solved in G1)
    std::array<uint8_t, 8> E_posPerm = {
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
    std::array<uint8_t, 8> C_posPerm = {
        cube.getPieceInd(EPIECE::ULB),
        cube.getPieceInd(EPIECE::ULF),
        cube.getPieceInd(EPIECE::DLF),
        cube.getPieceInd(EPIECE::DLB),
        cube.getPieceInd(EPIECE::DRB),
        cube.getPieceInd(EPIECE::DRF),
        cube.getPieceInd(EPIECE::URF),
        cube.getPieceInd(EPIECE::URB),
    };

    // stores the positions of the 4 edges that need to be brought back to the E-slice
    // a solved E-slice dictates a solved S-slice (vice versa), only 1 slice has to be considered
    std::array<uint8_t, 4> E_posComb;
    // same as the edges, spliting the corners into 2 tetrads - one the contains all the corners
    // with even indices and one that contains all the corners with odd indices
    std::array<uint8_t, 4> C_posComb;
    std::array<uint8_t, 4> C_posCombEven;
    std::array<uint8_t, 4> C_posCombOdd;

    for (uint8_t i = 0, e = 0, c = 0, ce = 0, co = 0; i < 8; ++i)
    {
        // indices of the E-slice edges are 4, 5, 6, 7
        if (E_posPerm[i] == 4 || E_posPerm[i] == 5 ||
            E_posPerm[i] == 6 || E_posPerm[i] == 7)
        {
            E_posComb[e++] = i + 1;
        }
        // even tetrad
        if (C_posPerm[i] % 2 == 0)
        {
            C_posComb[c++] = i + 1;
        }

        // splits the corners into their tetrads
        if (C_posPerm[i] & 1) C_posCombOdd[co++]  = C_posPerm[i];
        else                  C_posCombEven[ce++] = C_posPerm[i];
    }

    // new permutation with fixed tetrads (keeping the relative order from the original permutation)
    std::array<uint8_t, 8> C_tetradsPerm;
    for (uint8_t i = 0, ce = 0, co = 0; i < 8; ++i)
    {
        if (i & 1) C_tetradsPerm[i] = C_posCombOdd[co++];
        else       C_tetradsPerm[i] = C_posCombEven[ce++];
    }

    // imitate a move (half twists only) in an array
    auto C_imitateMove = [](EMOVE move, std::array<uint8_t, 8>& tetradsPerm) {
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
            throw std::logic_error("G2_G3_database::getInd invalid enum value " + (int)move);
        }
    };

    // solve the even tetrad (ULB DLF DRB URF)
    const std::array<std::vector<EMOVE>, 4> C_evenTetradSolvingMoves = {{ {EMOVE::U2, EMOVE::L2, EMOVE::B2}, {EMOVE::D2, EMOVE::F2}, {EMOVE::R2} }};

    std::cout << "initial: ";
    for (auto c : C_tetradsPerm) std::cout << (int)c << " ";
    std::cout << std::endl;

    for (uint8_t i = 0; i < 8; i += 2)
    {
        if (C_tetradsPerm[i] == i) continue;

        for (auto move : C_evenTetradSolvingMoves[i / 2])
        {
            C_imitateMove(move, C_tetradsPerm);

            if (C_tetradsPerm[i] == i) break;
            // reverse last move
            else C_imitateMove(move, C_tetradsPerm);
        }
    }

    std::cout << "after: ";
    for (auto c : C_tetradsPerm) std::cout << (int)c << " ";
    std::cout << std::endl;

    // solve ULF (first corner of the odd tetrad)
    std::array<std::array<EMOVE, 4>, 3> C_oddTetradSolvingMoves = {{
        {EMOVE::F2, EMOVE::L2, EMOVE::F2, EMOVE::U2},
        {EMOVE::U2, EMOVE::F2, EMOVE::U2, EMOVE::L2},
        {EMOVE::L2, EMOVE::U2, EMOVE::L2, EMOVE::F2}
    }};

//    std::cout << "initial: ";
//    for (auto c : C_tetradsPerm) std::cout << (int)c << " ";
//    std::cout << std::endl;

    if (C_tetradsPerm[1] != 1)
    {
        for (uint8_t i = 0; i < 3; ++i)
        {
            for (uint8_t j = 0; j < 4; ++j)
            {
                C_imitateMove(C_oddTetradSolvingMoves[i][j], C_tetradsPerm);
            }
//            std::cout << "after" << (int)i << ": ";
//            for (auto c : C_tetradsPerm) std::cout << (int)c << " ";
//            std::cout << std::endl;
            if (C_tetradsPerm[1] == 1) break;
            // reverse last move
            for (int k = 3; k >= 0; --k)
            {
                C_imitateMove(C_oddTetradSolvingMoves[i][k], C_tetradsPerm);
            }
        }
    }

//    for (auto c : C_tetradsPerm) std::cout << (int)c << " ";
//    std::cout << std::endl;

    // permutation of the remaining 3 odd pieces
    std::array<uint8_t, 3> C_oddTetradPerm = { (uint8_t)((C_tetradsPerm[3] >> 1) - 1), (uint8_t)((C_tetradsPerm[5] >> 1) - 1), (uint8_t)((C_tetradsPerm[7] >> 1) - 1) };

    uint32_t E_ind = combIndexer4.getInd(E_posComb);
    uint32_t C_ind = combIndexer4.getInd(C_posComb);
    uint32_t factor = permIndexer3.getInd(C_oddTetradPerm);

    return factor;

    return C_ind * 70 + E_ind;
}
