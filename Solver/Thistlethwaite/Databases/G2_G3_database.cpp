#include "G2_G3_database.h"

uint32_t G2_G3_Database::getIndex(const Rubiks& cube) const
{
    using EEDGE   = Rubiks::EEDGE;
    using ECORNER = Rubiks::ECORNER;
    using ECOLOUR = Rubiks::ECOLOUR;

    using pair_t  = std::array<uint8_t, 2>;

    // store the location of all edges in the E and S slice
    std::array<uint8_t, 8> ePosPerm = {
        cube.getEdgeInd({cube.getColour(EEDGE::UL), cube.getColour(EEDGE::LU)}),
        cube.getEdgeInd({cube.getColour(EEDGE::UR), cube.getColour(EEDGE::RU)}),
        cube.getEdgeInd({cube.getColour(EEDGE::DL), cube.getColour(EEDGE::LD)}),
        cube.getEdgeInd({cube.getColour(EEDGE::DR), cube.getColour(EEDGE::RD)}),
        cube.getEdgeInd({cube.getColour(EEDGE::RF), cube.getColour(EEDGE::FR)}),
        cube.getEdgeInd({cube.getColour(EEDGE::RB), cube.getColour(EEDGE::BR)}),
        cube.getEdgeInd({cube.getColour(EEDGE::LF), cube.getColour(EEDGE::FL)}),
        cube.getEdgeInd({cube.getColour(EEDGE::LB), cube.getColour(EEDGE::BL)}),
    };

    std::array<uint8_t, 8> cPosPerm = {
        cube.getCornerInd({ cube.getColour(ECORNER::LUB), cube.getColour(ECORNER::ULB), cube.getColour(ECORNER::BLU) }), // pos0
        cube.getCornerInd({ cube.getColour(ECORNER::LUF), cube.getColour(ECORNER::ULF), cube.getColour(ECORNER::FLU) }), // pos1
        cube.getCornerInd({ cube.getColour(ECORNER::LDF), cube.getColour(ECORNER::DLF), cube.getColour(ECORNER::FLD) }), // pos2
        cube.getCornerInd({ cube.getColour(ECORNER::LDB), cube.getColour(ECORNER::DLB), cube.getColour(ECORNER::BLD) }), // pos3
        cube.getCornerInd({ cube.getColour(ECORNER::RDB), cube.getColour(ECORNER::DRB), cube.getColour(ECORNER::BRD) }), // pos4
        cube.getCornerInd({ cube.getColour(ECORNER::RDF), cube.getColour(ECORNER::DRF), cube.getColour(ECORNER::FRD) }), // pos5
        cube.getCornerInd({ cube.getColour(ECORNER::RUB), cube.getColour(ECORNER::URB), cube.getColour(ECORNER::BRU) }), // pos6
        cube.getCornerInd({ cube.getColour(ECORNER::RUF), cube.getColour(ECORNER::URF), cube.getColour(ECORNER::FRU) }), // pos7
    };

    // find where the corners are and update their positions
    auto setPairPos = [&](pair_t& pair) {
        for (uint8_t i = 0; i < 8; ++i)
        {
            if (pair[0] == cPosPerm[i])
            {
                pair[0] = i;
            }
            if (pair[1] == cPosPerm[i])
            {
                pair[1] = i;
            }
        }
    };

    // why is this not working?? std::array<pair_t, 4> cPairPerm = { {0, 2}, {4, 6}, {1, 3}, {5, 7} };
    pair_t p0 = { 0, 2 };
    pair_t p1 = { 4, 6 };
    pair_t p2 = { 1, 3 };
    pair_t p3 = { 5, 7 };

    // store the position of each corner
    std::array<pair_t, 4> cPairPerm = { p0, p1, p2, p3 };

    for (pair_t& pair : cPairPerm)
    {
        setPairPos(pair);
    }

    // store the positions of the 4 edges that need to be brought back to the E-slice
    // a solved E-slice dictates a solved S-slice (vice versa), only 1 slice has to be considered
    std::array<uint8_t, 4> ePosComb;

    for (uint8_t i = 0, e = 0; i < 8 && e < 4; ++i)
    {
        // indices of the E-slice edges are 4, 5, 6, 7
        if (ePosPerm[i] == 4 || ePosPerm[i] == 5 ||
            ePosPerm[i] == 6 || ePosPerm[i] == 7)
        {
            ePosComb[e++] = i + 1;
        }
    }

    uint32_t eInd = combIndexer.getInd(ePosComb); // edge
    uint32_t cInd = 0;                            // corner
    uint32_t pInd = 0;                            // parity (0 = even, 1 = odd)

    // check if parity is even or odd
    // this works like a bubble-sort, but instead 0 / 1 is switched based on
    // how many swaps were made from the root position (0=even 1=odd)
    for (uint8_t i = 0; i < 8; ++i)
    {
        for (uint8_t j = i + 1; j < 8; ++j)
        {
            pInd ^= cPosPerm[i] < cPosPerm[j];
        }
    }

    // pairRank[0] = 0..8C2, pairRank[1] = 0..6C2, pairRank[2] = 0..4C2
    uint8_t pairRank[3];
    bool    seen[8]{};

    // loop through the first 3 pairs (4th pair is forced by the first 3)
    for (uint8_t i = 0; i < 3; ++i)
    {
        // order the pairs in ascending order
        if (cPairPerm[i][0] > cPairPerm[i][1])
        {
            std::swap(cPairPerm[i][0], cPairPerm[i][1]);
        }

        uint8_t rank = 0;
        uint8_t relativePairRank[8][8];

        // set the rank of each pair (accounting for previous pairs)
        for (uint8_t x = 0; x < 8; ++x)
        {
            if (seen[x]) continue;
            for (uint8_t y = x + 1; y < 8; ++y)
            {
                if (seen[y]) continue;
                relativePairRank[x][y] = rank++;
            }
        }

        // get the rank of the 3 pairs
        pairRank[i] = relativePairRank[cPairPerm[i][0]][cPairPerm[i][1]];

        seen[cPairPerm[i][0]] = true;
        seen[cPairPerm[i][1]] = true;
    }

    // 0..8C2 - 1 * (6C2 * 4C2 * 2C2) + 0..6C2 - 1 * (4C2 * 2C2) + 0..4C2 - 1 = 0..2519
    cInd = pairRank[0] * 90 + pairRank[1] * 6 + pairRank[2];

    // (0..2519 * 70 + 0..69) * 2 + 0..1 = 0..352799
    return cInd;
    //return (cInd * 70 + eInd) * 2 + pInd;
}
