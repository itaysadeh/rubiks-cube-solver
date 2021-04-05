#include "G2_G3_database.h"

uint32_t G2_G3_Database::getIndex(const Rubiks& cube) const
{
    using EPIECE = Rubiks::EPIECE;
    using pair_t = std::array<uint8_t, 2>;

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

    // root pair positions
    constexpr std::array<pair_t, 4> C_rootPairPos = {{ {0, 2}, {4, 6}, {1, 3}, {5, 7} }};

    // finds the positions of a pair and writes it to result
    auto setPairPos = [&](const pair_t& target, pair_t& result) {
        for (uint8_t i = 0; i < 8; ++i)
        {
            if (target[0] == C_posPerm[i]) result[0] = i;
            if (target[1] == C_posPerm[i]) result[1] = i;
        }
    };

    std::array<pair_t, 4> C_pairPerm;
    // stores the positions of the corners in a pair
    for (uint8_t i = 0; i < 4; ++i)
    {
        setPairPos(C_rootPairPos[i], C_pairPerm[i]);
    }

    // stores the positions of the 4 edges that need to be brought back to the E-slice
    // a solved E-slice dictates a solved S-slice (vice versa), only 1 slice has to be considered
    std::array<uint8_t, 4> E_posComb;

    for (uint8_t i = 0, e = 0; i < 8 && e < 4; ++i)
    {
        // indices of the E-slice edges are 4, 5, 6, 7
        if (E_posPerm[i] == 4 || E_posPerm[i] == 5 ||
            E_posPerm[i] == 6 || E_posPerm[i] == 7)
        {
            E_posComb[e++] = i + 1;
        }
    }

    uint32_t E_ind = combIndexer4.getInd(E_posComb); // edge
    uint32_t C_ind = 0;                              // corner
    uint32_t P_ind = 0;                              // parity (0 = even, 1 = odd)

    // checks if parity is even or odd
    for (uint8_t i = 0; i < 8; ++i)
    {
        for (uint8_t j = i + 1; j < 8; ++j)
        {
            P_ind ^= C_posPerm[i] < C_posPerm[j];
        }
    }

    uint8_t C_pairRank[3];
    bool seen[8]{};

    for (uint8_t i = 0; i < 3; ++i)
    {
        // order the corners in the pair in ascending order
        if (C_pairPerm[i][0] > C_pairPerm[i][1])
        {
            std::swap(C_pairPerm[i][0], C_pairPerm[i][1]);
        }

        uint8_t rank = 0;
        uint8_t C_relativePairRank[8][8];

        // set the rank of each pair (realtivly, accounting for previous pairs)
        for (uint8_t x = 0; x < 8; ++x)
        {
            if (seen[x]) continue;
            for (uint8_t y = x + 1; y < 8; ++y)
            {
                if (seen[y]) continue;
                C_relativePairRank[x][y] = rank++;
            }
        }

        // get the rank of the 3 pairs
        C_pairRank[i] = C_relativePairRank[C_pairPerm[i][0]][C_pairPerm[i][1]];

        seen[C_pairPerm[i][0]] = true;
        seen[C_pairPerm[i][1]] = true;
    }

    // (0..8C2 - 1) * (6C2 * 4C2 * 2C2) + (0..6C2 - 1) * (4C2 * 2C2) + (0..4C2 - 1) = 0..2519
    C_ind = C_pairRank[0] * 90 + C_pairRank[1] * 6 + C_pairRank[2];

    // (0..2519 * (8C4) + (0..8C4 - 1)) * 2 + 0|1 = 0..352799
    return (C_ind * 70 + E_ind) * 2 + P_ind;
}
